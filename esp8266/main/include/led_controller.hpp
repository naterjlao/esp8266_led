#ifndef __LED_CONTROLLER_HPP__
#define __LED_CONTROLLER_HPP__

#include <FastLED.h>
#include "protocol.hpp"
#include "led_lib.hpp"

namespace LED
{
    /// @note this must be changed according to hardware
    const int DATA_PIN = 16;

    class Controller
    {
    public:
        Controller(const int nLeds);
        ~Controller();
        void receive(const PROTOCOL::PAYLOAD& payload);
        void render(void);
    private:
        void setMode(const PROTOCOL::MODES mode);
        CRGB *leds;
        SETTINGS settings;
        MODE_FUNCTION mode;
        bool mode_change;
        bool refresh;
    };
};
#endif