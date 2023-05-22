#include <ArduinoBLE.h>
#include <mbed.h>
#include "RGB.h"
#include "RGB_R.h"
#include "rgb_speed.h"
#include <TinyGPS++.h>


void ArrayAdd(int data);

TinyGPSPlus gps;
UART gpsSerial(D5, D4, NC, NC);


using namespace mbed;
using namespace rtos;
using namespace std::chrono_literals;

Thread mobile_task;
Thread blue_task;
Thread gps_task;
Thread rgb_task;

char turningSignalData = ' ';
char previousSignalData = ' ';
float speed = 0;
int mobileDataArray[4] = { 255, 0, 0, 0 };
int mobileData;
int arrayLength = 0;
int flag = 0;
bool leftSignal = false;
bool rightSignal = false;
bool ledOn = false;

BLEService ledService("180A");
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

int myArray[4];

RGBLeds myRGBs_l = {
  .clear = &clearRGB,
  .slide = &SlideLEDs,
  .blink = &BinkLEDs,
  .accumulation = &accumulatedLEDs,
  .parallel = &parallel2string
};
RGBLeds *pRGB = &myRGBs_l;

RGBLeds_R myRGBs_r = {
  .clear_r = &clearRGB_r,
  .slide_r = &SlideLEDs_r,
  .blink_r = &BinkLEDs_r,
  .accumulation_r = &accumulatedLEDs_r,
  .parallel_r = &parallel2string_r
};
RGBLeds_R *pRGB_r = &myRGBs_r;

void rgbFunction() {
  for (;;) {
    if (ledOn) {
      if (leftSignal) {
        pRGB_r->clear_r();
        if (mobileDataArray[3] == 0) pRGB->slide(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
        if (mobileDataArray[3] == 1) pRGB->blink(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
        if (mobileDataArray[3] == 2) pRGB->accumulation(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
        if (mobileDataArray[3] == 3) pRGB->parallel(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
      } else strip.clear();
      if (rightSignal) {
        pRGB->clear();
        if (mobileDataArray[3] == 0) pRGB_r->slide_r(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
        if (mobileDataArray[3] == 1) pRGB_r->blink_r(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
        if (mobileDataArray[3] == 2) pRGB_r->accumulation_r(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
        if (mobileDataArray[3] == 3) pRGB_r->parallel_r(mobileDataArray[0], mobileDataArray[1], mobileDataArray[2]);
      } else strip1.clear();
    }
    if (!ledOn) {
      pRGB_r->clear_r();
      pRGB->clear();
      strip.clear();
      strip1.clear();
    }
    ThisThread::sleep_for(350ms);
  }
}

void mobileFunction() {
  for (;;) {
    BLEDevice central = BLE.central();
    if (central) {
      Serial.print("Connected to central: ");
      Serial.println(central.address());
      digitalWrite(LED_BUILTIN, HIGH);

      while (central.connected()) {
        if (switchCharacteristic.written()) {
          switchCharacteristic.value();
          Serial.println(switchCharacteristic.value());
          ArrayAdd(switchCharacteristic.value());
        }
      }
      Serial.print(F("Disconnected from central: "));
      Serial.println(central.address());
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  ThisThread::sleep_for(220ms);
}

void blueFunction() {
  for (;;) {
    if (Serial1.available()) {
      turningSignalData = Serial1.read();
      Serial.println(turningSignalData);
      if (turningSignalData != '0') {
        ledOn = true;
        Serial.println("LED ON");
      } else {
        ledOn = false;
        Serial.println("LED OFF");
      }
      if (turningSignalData == 'r') {
        rightSignal = true;
        leftSignal = false;
      }
      if (turningSignalData == 'l') {
        leftSignal = true;
        rightSignal = false;
      }
    }
    ThisThread::sleep_for(200ms);
  }
}

void gpsFunction() {
  for (;;) {
    // gpsSerial.begin(9600);
    while (gpsSerial.available()) {
      if (gps.encode(gpsSerial.read())) {
        if (gps.speed.isValid()) {
          speed = gps.speed.kmph();
        } else {
          speed = 0;
        }
      }
    }
    rgb_speed(speed);
    ThisThread::sleep_for(1s);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");
    while (1)
      ;
  }
  BLE.setLocalName("bikerHelmet");
  ledService.addCharacteristic(switchCharacteristic);
  BLE.addService(ledService);
  switchCharacteristic.writeValue(0);
  BLE.advertise();

  Serial1.begin(38400);
  gpsSerial.begin(9600);

  strip.begin();
  strip1.begin();
  strip2.begin();


  mobile_task.start(mobileFunction);
  blue_task.start(blueFunction);
  rgb_task.start(rgbFunction);
  gps_task.start(gpsFunction);
}

void loop() {
}

void ArrayAdd(int data) {
  for (int i = arrayLength; i < 4; i++) {
    mobileDataArray[i] = data;
  }
  arrayLength++;
  if (arrayLength == 4) arrayLength = 0;
}