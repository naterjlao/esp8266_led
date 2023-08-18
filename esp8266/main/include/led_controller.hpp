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

    /// @brief Function Pointer to the mode settings
    typedef void (*MODE_FUNCTION)(void);

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
        void render(void);
        void setMode(const MODES mode, const CRGB color, const uint8_t brightness);

        /// @todo privatize or remove
        void setColor(const CRGB color);
        void setBrightness(const uint8_t scale);
        void show();
    private:
        int nLeds;
        uint8_t data_pin;
        CRGB *leds;
        uint8_t brightness;
        MODE_FUNCTION mode;
        bool mode_change;


        void mode_off(void);
        void mode_solid(void);
        void mode_breathe(void);
        void mode_cycle(void);
        void mode_breathe_cycle(void);
        void mode_chaser(void);
    };
};
#endif