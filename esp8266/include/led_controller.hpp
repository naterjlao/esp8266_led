#ifndef __LED_CONTROLLER_HPP__
#define __LED_CONTROLLER_HPP__

#include <FastLED.h>

namespace LED
{
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
    }
    
    class Controller
    {
    public:
        Controller(const int nLeds);
        ~Controller();
        bool setMode(const MODES mode);
    private:
        int nLeds;
        CRGB *leds;
        MODE_FUNCTION current_mode;
        void mode_off(void);
        void mode_solid(void);
        void mode_breathe(void);
        void mode_cycle(void);
        void mode_breathe_cycle(void);
        void mode_chaser(void);
    };
};
#endif