#include <FastLED.h>

#include "include/led_controller.hpp"

// ----- PUBLIC FUNCTION IMPLEMENTATION ----- //

LED::Controller::Controller(const int nLeds)
{
    memset(&settings, 0, sizeof(settings));
    if (nLeds > 0)
    {
        this->settings.nLeds = nLeds;
        this->settings.color = CRGB::Black;
        this->settings.brightness = 0x0;

        this->leds = (CRGB *)malloc(sizeof(CRGB) * this->settings.nLeds);
        this->mode = 0;
        this->mode_change = false;
        this->refresh = false;

        // Set up Fast LED and wake up the LEDs
        FastLED.addLeds<NEOPIXEL, LED::DATA_PIN>(this->leds, this->settings.nLeds);
        FastLED.setBrightness(0xFF);
        for (size_t idx = 0; idx < this->settings.nLeds; ++idx)
        {
            delay(10); // this is needed for WDT
            this->leds[idx] = CRGB::White;
            FastLED.show();
        }

#if 0
        // Turn Off
        this->setMode(LED::OFF);
#else
        // testing playground
        this->settings.color = CRGB::Amethyst;
        this->settings.brightness = 0xFF;
        this->setMode(LED::SOLID);
#endif
    }
}

/// @brief Performs a single frame of LED rendering
/// @param
void LED::Controller::render(void)
{
    if (this->mode != 0)
    {
        // Invoke the Current Mode Function
        this->mode(this->leds, this->settings, this->mode_change);
        // Render LED Output
        if (this->refresh) FastLED.show();
        // For solid mode, don't refresh all the time
        this->refresh = this->mode != LED::mode_solid;
    }
}

// ----- PRIVATE CLASS METHODS ----- //

void LED::Controller::setMode(const LED::MODES mode)
{
    /// @todo for now, invoke mode change if this is called
    mode_change = true;

    // Set new Mode Function
    switch (mode)
    {
    case LED::OFF:
        this->settings.color = CRGB::Black;
        this->settings.brightness = 0x00;
    case LED::SOLID:
        this->mode = LED::mode_solid;
        this->refresh = true;
        break;
    case LED::BREATHE:
        this->mode = LED::mode_breathe;
        break;
    case LED::CYCLE:
        this->mode = LED::mode_cycle;
        break;
    case LED::BREATHE_CYCLE:
        this->mode = LED::mode_breathe_cycle;
        break;
    case LED::CHASER:
        this->mode = LED::mode_chaser;
        break;
    default:
        break;
    }
}
