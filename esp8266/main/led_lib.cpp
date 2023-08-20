#include "include/led_lib.hpp"

/// @brief Utility Function, sets all LEDs to a color
/// @param leds LED array
/// @param nLeds Number of LEDs
/// @param color Color
static void set_all_leds(CRGB *leds, const int nLeds, const CRGB color)
{
    for (size_t idx = 0; leds != 0 && idx < nLeds; ++idx)
    {
        leds[idx] = color;
    }
}

/// @brief LED Solid Mode. All LEDs set to static color and brightness
/// @param leds LED array
/// @param settings Mode Settings Parameters
/// @param mode_change Mode Change Flag
void LED::mode_solid(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change)
{
    if (leds != 0 && mode_change)
    {
        FastLED.setBrightness(settings.brightness);
        set_all_leds(leds, settings.nLeds, settings.color);
        mode_change = false;
    }
}

/// @brief LED Breathe Mode. All LEDs set to static color but brightness increases and decreases.
/// @param leds LED array
/// @param settings Mode Settings Parameters
/// @param mode_change Mode Change Flag
void LED::mode_breathe(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change)
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

    /// @todo figure out rate-counter
    // Increase and Decrease Brightness
    brightness += increment ? 1 : -1;
    increment = (brightness == 0x00) ? true : increment;
    increment = (brightness == 0xFF) ? false : increment;

    // Set Brightness
    FastLED.setBrightness(brightness);
}

/// @brief LED Cycle Mode. All LEDs change colors but brightness is static.
/// @param leds LED array
/// @param settings Mode Settings Parameters
/// @param mode_change Mode Change Flag
void LED::mode_cycle(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change)
{
    /// @todo
}

/// @brief LED Breathe+Cycle Mode. All LEDs change colors and brightness increases and decreases.
/// @param leds LED array
/// @param settings Mode Settings Parameters
/// @param mode_change Mode Change Flag
void LED::mode_breathe_cycle(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change)
{
    /// @todo
}

/// @brief LED Chaser Mode. A section of LEDs "travels" across the LED strip.
/// @param leds LED array
/// @param settings Mode Settings Parameters
/// @param mode_change Mode Change Flag
void LED::mode_chaser(CRGB *leds, const LED::SETTINGS &settings, bool &mode_change)
{
    /// @todo
}
