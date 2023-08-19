#ifndef __LED_LIB_HPP__
#define __LED_LIB_HPP__

#include <FastLED.h>

namespace LED
{
    /// @brief Current LED Settings
    typedef struct
    {
        int nLeds;
        CRGB color;
        uint8_t brightness;
    } SETTINGS;

    /// @brief Current Mode
    typedef void (*MODE_FUNCTION)(CRGB*, const SETTINGS&, bool&);

    /// @brief Defines the list of colors used for CYCLE mode
    const CRGB COLORS[] =
    {
        CRGB::Red,
        CRGB::Orange,
        CRGB::Yellow,
        CRGB::Green,
        CRGB::Blue,
        CRGB::Purple
    };

    void set_all_leds(CRGB *leds, const int nLeds, const CRGB color);

    void mode_solid(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change);
    void mode_breathe(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change);
    void mode_cycle(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change);
    void mode_breathe_cycle(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change);
    void mode_chaser(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change);
}
#endif