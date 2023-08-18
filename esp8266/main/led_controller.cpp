#include "include/led_controller.hpp"
#include <FastLED.h>

// ----- PRIVATE FUNCTION PROTOTYPES ----- //
static void set_all_leds(CRGB* leds, const int nLeds, const CRGB color);

static void mode_solid(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change);
static void mode_breathe(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change);
static void mode_cycle(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change);
static void mode_breathe_cycle(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change);
static void mode_chaser(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change);


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

        // Set up Fast LED and wake up the LEDs
        FastLED.addLeds<NEOPIXEL, LED::DATA_PIN>(this->leds, this->settings.nLeds);
        FastLED.setBrightness(0xFF);
        for (size_t idx = 0; idx < this->settings.nLeds; ++idx)
        {
            this->leds[idx] = CRGB::White;
            FastLED.show();
        }
        delay(1000);

        // Turn Off
        this->setMode(LED::OFF);
    }
}

void LED::Controller::setColor(const CRGB color)
{
    this->settings.color = color;
}

void LED::Controller::setBrightness(const uint8_t brightness)
{
    this->settings.brightness = brightness;
}

void LED::Controller::setMode(const LED::MODES mode)
{
    /// @todo for now, invoke mode change if this is called
    mode_change = true;

    // Set new Mode Function
    switch (mode)
    {
    case LED::OFF:
        this->setColor(CRGB::Black);
        this->setBrightness(0x0);
    case LED::SOLID:
        this->mode = mode_solid;
        break;
    case LED::BREATHE:
        this->mode = mode_breathe;
        break;
    case LED::CYCLE:
        this->mode = mode_cycle;
        break;
    case LED::BREATHE_CYCLE:
        this->mode = mode_breathe_cycle;
        break;
    case LED::CHASER:
        this->mode = mode_chaser;
        break;
    default:
        break;
    }
}

void LED::Controller::render(void)
{
    if (this->mode != 0)
    {
        // Invoke the Current Mode Function
        this->mode(this->leds, this->settings, this->mode_change);
        // Render LED Output
        FastLED.show();
        /// @todo for solid mode, don't refresh all the time
    }   
}

// ----- PRIVATE FUNCTION IMPLEMENTATION ----- //

static void set_all_leds(CRGB *leds, const int nLeds, const CRGB color)
{
    for (size_t idx = 0; leds != 0 && idx < nLeds; ++idx)
    {
        leds[idx] = color;
    }
}

static void mode_solid(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change)
{
    if (leds != 0 && mode_change)
    {
        FastLED.setBrightness(settings.brightness);
        set_all_leds(leds, settings.nLeds, settings.color);
        mode_change = false;
    }
}

static void mode_breathe(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change)
{
    static uint8_t brightness = 0x0;
    static bool increment = true;
    if (mode_change)
    {
        // First call - reset brightness back to zero and set color
        brightness = 0x0;
        increment = true;
        set_all_leds(leds, settings.nLeds, settings.color);
        mode_change = false;
    }

    // Increase and Decrease Brightness
    brightness += increment ? 1 : -1;
    increment = (brightness == 0x00) ? true : increment;
    increment = (brightness == 0xFF) ? false : increment;

    // Set Brightness
    FastLED.setBrightness(brightness);
}

static void mode_cycle(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change)
{
    /// @todo
}

static void mode_breathe_cycle(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change)
{
    /// @todo
}

static void mode_chaser(CRGB* leds, const LED::SETTINGS& settings, bool& mode_change)
{
    /// @todo
}