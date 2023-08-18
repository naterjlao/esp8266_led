#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 15
#define DELAY 30
CRGB leds[NUM_LEDS];
static const CRGB COLORS[] = {
  CRGB::Red,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Purple
};

size_t idx;
size_t color_idx;
bool forward;
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Blank Out All LEDs
  idx = 0;
  FastLED.setBrightness(0xFF);
  while (idx < NUM_LEDS) {
    leds[idx++] = CRGB::White;
    FastLED.show();
  }

  // Reset Indices
  idx = 0;
  color_idx = 0;
  forward = true;

  Serial.begin(9600);
}

unsigned char intensity = 0;
unsigned int hex = 0;
bool increment = true;
void loop() {
#if 0
  // Chaser
  leds[idx] = COLORS[color_idx];
  leds[((idx == 0) ? (NUM_LEDS - 1) : (idx - 1))] = CRGB::Black;
  FastLED.show();
  delay(DELAY);

  // Increment Indices
  if (idx < NUM_LEDS)
  {
    ++idx;
  }
  else
  {
    idx = 0; // Start over

    // Set next color
    ++color_idx;
    if (color_idx >= (sizeof(COLORS) / sizeof(CRGB))) color_idx = 0;
  }
#elif 1
  int _delay = 20;
  if (intensity == (0xFF/4))
  {
    increment = false;
    _delay = 2000;
  }
  if (intensity == 0x0)
  {
    increment = true;
    _delay = 100;
    // Set next color
    ++color_idx;
    if (color_idx >= (sizeof(COLORS) / sizeof(CRGB))) color_idx = 0;
  }
  intensity += increment ? 1 : -1;
  FastLED.setBrightness(intensity);
  idx = 0;  
  while (idx < NUM_LEDS) {
    leds[idx++] = COLORS[color_idx];
  }
  delay(_delay);
  FastLED.show();

#elif 0
  ++hex;
  hex = hex % 0xFFFFFF;

  CRGB color;
  color.r = (hex >> 0) % 0xFF;
  color.g = (hex >> 8) % 0xFF;
  color.b = (hex >> 16) % 0xFF;
  idx = 0;
  while (idx < NUM_LEDS) {
    leds[idx++] = color;
  }
  FastLED.show();

#endif
}
