#include "include/led_controller.hpp"
#include <FastLED.h>

LED::Controller::Controller(const int nLeds)
{
    if (nLeds > 0)
    {
        this->nLeds = nLeds;
        this->leds = (CRGB *)malloc(sizeof(CRGB) * this->nLeds);
        this->brightness = 0x0;
        this->mode = 0;
        this->mode_change = false;

        // Set up Fast LED and wake up the LEDs
        FastLED.addLeds<NEOPIXEL, LED::DATA_PIN>(this->leds, this->nLeds);
        for (size_t idx = 0; idx < this->nLeds; ++idx)
        {
            this->leds[idx] = CRGB::White;
            this->show();
        }
        delay(1000);

        // Turn Off
    }
    else
    {
        this->nLeds = 0;
        this->leds = 0;
    }
}

void LED::Controller::render(void)
{
    if (this->mode != 0)
    {
        this->mode();
    }
}

void LED::Controller::setMode(const LED::MODES mode, const CRGB color, const uint8_t brightness)
{
    switch (mode)
    {
    case LED::OFF:
        break;
    case LED::SOLID:
        break;
    case LED::BREATHE:
        break;
    case LED::CYCLE:
        break;
    case LED::BREATHE_CYCLE:
        break;
    case LED::CHASER:
        break;
    default:
        break;
    }
}

void LED::Controller::setColor(const CRGB color)
{
    for (size_t idx = 0; idx < this->nLeds; ++idx)
    {
        this->leds[idx] = color;
    }
}

void LED::Controller::setBrightness(const uint8_t scale)
{
    this->brightness = scale;
}

void LED::Controller::show()
{
    FastLED.show();
}