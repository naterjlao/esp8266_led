#ifndef __LED_CONTROLLER_HPP__
#define __LED_CONTROLLER_HPP__

#include <FastLED.h>
#include "led_lib.hpp"

namespace LED
{
    const int DATA_PIN = 15;

    class Controller
    {
    public:
        Controller(const int nLeds);
        ~Controller();
        //void setColor(const CRGB color);
        //void setBrightness(const uint8_t brightness);
        void render(void);
    private:
        void setMode(const MODES mode);
        CRGB *leds;
        SETTINGS settings;
        MODE_FUNCTION mode;
        bool mode_change;
        bool refresh;
    };
};
#endif