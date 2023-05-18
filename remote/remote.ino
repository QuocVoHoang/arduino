#include <SoftwareSerial.h>

#define LeftButton 5
#define RightButton 4
#define Signal_Left 8
#define Signal_Right 7

SoftwareSerial SigNal(3, 2);

bool leftState, rightState;
int leftNum = 0, rightNum = 0;
int flag_l = 0, flag_r = 0;

void setup() {
  SigNal.begin(38400);
  Serial.begin(9600);
  pinMode(LeftButton, INPUT);
  pinMode(RightButton, INPUT);
  pinMode(Signal_Right, OUTPUT);
  pinMode(Signal_Left, OUTPUT);
}

void loop() {
  leftState = digitalRead(LeftButton);

  if (leftState == LOW) {
    while (digitalRead(LeftButton) == LOW)
      ;
    flag_l ^= 1;

    leftNum++;
    if (leftNum == 1) {
      SigNal.print('l');
      Serial.println('l');
    } else if (leftNum != 1) {
      SigNal.print('0');
      Serial.println('0');
      leftNum = 0;
    }
  }
  if (flag_l == 1) {
    flag_r = 0;
    digitalWrite(Signal_Left, HIGH);
  } else {
    digitalWrite(Signal_Left, LOW);
  }

  rightState = digitalRead(RightButton);
  if (rightState == LOW) {
    while (digitalRead(RightButton) == LOW)
      ;

    flag_r ^= 1;

    rightNum++;
    if (rightNum == 1) {
      SigNal.print('r');
      Serial.println('r');
    } else if (rightNum != 1) {
      SigNal.print('0');
      Serial.println('0');
      rightNum = 0;
    }
  }
  if (flag_r == 1) {
    flag_l = 0;
    digitalWrite(Signal_Right, HIGH);
  } else {
    digitalWrite(Signal_Right, LOW);
  }
}
