#include <Adafruit_NeoPixel.h>

#define LED_PIN D7 // change this to match the pin you connected the LED strip to
#define NUM_LEDS 5 // change this to match the number of LEDs in your strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
  uint8_t count=5;
typedef struct{
  void (*clear)();
  void (*slide)(int, int, int);
  void (*blink)(int, int, int);
  void (*accumulation)(int, int, int);
  void (*parallel)(int, int, int);
}RGBLeds;

void clearRGB()
{
  for(int i=0; i<NUM_LEDS; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}
void SlideLEDs(int red, int green, int blue)
{
  /*Slide LEDs*/
  for(int i=0; i<NUM_LEDS-2; i++)
  {
      strip.setPixelColor(i, strip.Color(red, green, blue));
      strip.setPixelColor(i+1, strip.Color(red, green, blue));
      strip.setPixelColor(i+2, strip.Color(red, green, blue));
      strip.show();
      delay(50);
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.setPixelColor(i+1, strip.Color(0, 0, 0));
      strip.setPixelColor(i+2, strip.Color(0, 0, 0));
      strip.show();
      delay(50);
  }
}
void BinkLEDs(int red, int green, int blue)
{
  /*Blink LEDs*/

    for(int i=0; i<NUM_LEDS; i++)
    {
    strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    strip.show();
    delay(100);
    for(int i=0; i<NUM_LEDS; i++)
    {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(50);
}
void accumulatedLEDs(int red, int green, int blue)
{

  /*accumulated LEDs*/
    for(int i=0; i<count; i++)
    {
        strip.setPixelColor(i, strip.Color(red, green, blue));
        strip.show();
        delay(50);
        strip.setPixelColor(i, strip.Color(0, 0, 0));
        strip.show();
        delay(50);
    }
    count --;
    strip.setPixelColor(count, strip.Color(red, green, blue));
    if(count==0) count=NUM_LEDS;
}
void parallel2string(int red, int green, int blue)
{
/*2 parallel string */
  for(int i=0; i<NUM_LEDS/2; i++)
  {
      strip.setPixelColor(i, strip.Color(red, green, blue));
      strip.setPixelColor(NUM_LEDS/2+i, strip.Color(red, green, blue));
      strip.show();
      delay(50);
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.setPixelColor(NUM_LEDS/2+i, strip.Color(0, 0, 0));
      strip.show();
      delay(50);
  }
}





