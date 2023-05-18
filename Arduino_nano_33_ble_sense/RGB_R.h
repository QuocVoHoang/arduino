#include <Adafruit_NeoPixel.h>

#define LED_PIN_R D6 // change this to match the pin you connected the LED strip1 to
#define NUM_LEDS_R 5 // change this to match the number of LEDs in your strip1

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS_R, LED_PIN_R, NEO_GRB + NEO_KHZ800);
  uint8_t count_r=5;
typedef struct{
  void (*clear_r)();
  void (*slide_r)(int, int, int);
  void (*blink_r)(int, int, int);
  void (*accumulation_r)(int, int, int);
  void (*parallel_r)(int, int, int);
}RGBLeds_R;

void clearRGB_r()
{
  for(int i=0; i<NUM_LEDS_R; i++)
  {
    strip1.setPixelColor(i, strip1.Color(0, 0, 0));
  }
  strip1.show();
}
void SlideLEDs_r(int red, int green, int blue)
{
  /*Slide LEDs*/
  for(int i=0; i<NUM_LEDS_R-2; i++)
  {
      strip1.setPixelColor(i, strip1.Color(red, green, blue));
      strip1.setPixelColor(i+1, strip1.Color(red, green, blue));
      strip1.setPixelColor(i+2, strip1.Color(red, green, blue));
      strip1.show();
      delay(50);
      strip1.setPixelColor(i, strip1.Color(0, 0, 0));
      strip1.setPixelColor(i+1, strip1.Color(0, 0, 0));
      strip1.setPixelColor(i+2, strip1.Color(0, 0, 0));
      strip1.show();
      delay(50);
  }
}
void BinkLEDs_r(int red, int green, int blue)
{
  /*Blink LEDs*/

    for(int i=0; i<NUM_LEDS_R; i++)
    {
    strip1.setPixelColor(i, strip1.Color(red, green, blue));
    }
    strip1.show();
    delay(100);
    for(int i=0; i<NUM_LEDS_R; i++)
    {
    strip1.setPixelColor(i, strip1.Color(0, 0, 0));
    }
    strip1.show();
    delay(50);
}
void accumulatedLEDs_r(int red, int green, int blue)
{

  /*accumulated LEDs*/
    for(int i=0; i<count_r; i++)
    {
        strip1.setPixelColor(i, strip1.Color(red, green, blue));
        strip1.show();
        delay(50);
        strip1.setPixelColor(i, strip1.Color(0, 0, 0));
        strip1.show();
        delay(50);
    }
    count_r --;
    strip1.setPixelColor(count_r, strip1.Color(red, green, blue));
    if(count_r==0) count_r=NUM_LEDS_R;
}
void parallel2string_r(int red, int green, int blue)
{
/*2 parallel string */
  for(int i=0; i<NUM_LEDS_R/2; i++)
  {
      strip1.setPixelColor(i, strip1.Color(red, green, blue));
      delay(50);
      strip1.show();
      strip1.setPixelColor(NUM_LEDS_R/2+i, strip1.Color(red, green, blue));
      delay(50);
      strip1.show();
  }
}





