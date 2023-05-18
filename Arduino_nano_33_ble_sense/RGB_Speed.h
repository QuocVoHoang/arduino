#include <Adafruit_NeoPixel.h>

#define LED_PIN D8 // change this to match the pin you connected the LED strip to
#define NUM_LEDS 5 // change this to match the number of LEDs in your strip

Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
void rgb_speed(float speed)
{
  if(speed >10) 
  {
    for(int i=0; i<NUM_LEDS; i++) strip2.setPixelColor(i, strip2.Color(0, 255, 0));
  }
  else if(speed >=4 && speed <=10) 
  {
    for(int i=0; i<NUM_LEDS; i++) strip2.setPixelColor(i, strip2.Color(255, 255, 0));
  }
  else {
    for(int i=0; i<NUM_LEDS; i++) strip2.setPixelColor(i, strip2.Color(0, 0, 255));
  }
  strip2.show();
}