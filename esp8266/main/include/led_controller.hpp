#ifndef __LED_CONTROLLER_HPP__
#define __LED_CONTROLLER_HPP__

#include <FastLED.h>

namespace LED
{
    const int DATA_PIN = 15;

    /// @brief Defines the operational modes for the LED strip.
    enum MODES
    {
        OFF = 0x0,
        SOLID = 0x1,
        BREATHE = 0x2,
        CYCLE = 0x3,
        BREATHE_CYCLE = 0x4,
        CHASER = 0x5
    };

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

    class Controller
    {
    public:
        Controller(const int nLeds);
        ~Controller();
        void setColor(const CRGB color);
        void setBrightness(const uint8_t brightness);
        void setMode(const MODES mode);
        void render(void);
    private:
        CRGB *leds;
        SETTINGS settings;
        MODE_FUNCTION mode;
        bool mode_change;
    };
};
#endif