#include <Adafruit_NeoPixel.h>

#define LED_PIN_speed D8  // change this to match the pin you connected the LED strip to
#define NUM_LEDS_speed 5  // change this to match the number of LEDs in your strip

Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS_speed, LED_PIN_speed, NEO_GRB + NEO_KHZ800);
void rgb_speed(float speed) {
  if (speed >= 5 && speed <= 10) {
    for (int i = 0; i < NUM_LEDS_speed; i++) strip2.setPixelColor(i, strip2.Color(255, 255, 0));
    strip2.show();
  } else if (speed < 5) {
    for (int i = 0; i < NUM_LEDS_speed; i++) {
      strip2.setPixelColor(i, strip2.Color(255, 0, 0));
    }
    strip2.show();
  } else{
    strip2.clear();
    strip2.show();
  }
}