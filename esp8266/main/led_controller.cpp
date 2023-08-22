#include <FastLED.h>

#include "include/led_controller.hpp"

// ----- PUBLIC FUNCTION IMPLEMENTATION ----- //

/// @brief Allocates the LED Controller object.
/// @param nLeds 
LED::Controller::Controller(const int nLeds)
{
    memset(&settings, 0, sizeof(settings));
    if (nLeds > 0)
    {
        // Initialize Settings
        this->settings.nLeds = nLeds;
        this->settings.rate = 0xFFFF;
        this->settings.color = CRGB::Black;
        this->settings.brightness = 0x0;

        // Allocate LEDs
        this->leds = (CRGB *)malloc(sizeof(CRGB) * this->settings.nLeds);

        // Set Current Mode and Reset Flags
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

        // Turn Off LEDs and set to Ready State
        this->setMode(PROTOCOL::OFF);
    }
}

/// @brief Parses the received payload and sets LED Controller settings based on the user request.
/// @param payload
void LED::Controller::receive(const PROTOCOL::PAYLOAD &payload)
{
    // Verify Message ID
    /// @note the ESP8266 architecture is little-endian, byte-swapping is necessary
    if (PROTOCOL::MESSAGE_ID == __ntohl(payload.message_id))
    {
        // Set Rate
        this->settings.rate = __ntohs(payload.rate);

        // Set Brightness and RGB
        const uint32_t rgba = __ntohl(payload.rgba);
        this->settings.brightness = rgba & 0xFF;
        const uint8_t red = (rgba >> 24) & 0xFF;
        const uint8_t green = (rgba >> 16) & 0xFF;
        const uint8_t blue = (rgba >> 8) & 0xFF;
        this->settings.color = CRGB(red, green, blue);

        // Set Mode
        this->setMode(payload.mode_cmd); // no byte-swap, 8-bit field
    }
}

/// @brief Performs a single frame of LED rendering
void LED::Controller::render(void)
{
    if (this->mode != 0)
    {
        // Invoke the Current Mode Function
        this->mode(this->leds, this->settings, this->mode_change);
        // Render LED Output
        if (this->refresh)
            FastLED.show();
        // For solid mode, don't refresh all the time
        this->refresh = this->mode != LED::mode_solid;
    }
}

// ----- PRIVATE CLASS METHODS ----- //

/// @brief Helper Function, sets the Current Mode Function pointer based on Mode Label enum.
/// @param mode Mode Label enum.
void LED::Controller::setMode(const PROTOCOL::MODES mode)
{
    /// @todo for now, invoke mode change if this is called
    this->mode_change = true;
    this->refresh = true;

    // Set new Mode Function
    switch (mode)
    {
    case PROTOCOL::OFF:
        this->settings.color = CRGB::Black;
        this->settings.brightness = 0x00;
    case PROTOCOL::SOLID:
        this->mode = LED::mode_solid;
        break;
    case PROTOCOL::BREATHE:
        this->mode = LED::mode_breathe;
        break;
    case PROTOCOL::CYCLE:
        this->mode = LED::mode_cycle;
        break;
    case PROTOCOL::BREATHE_CYCLE:
        this->mode = LED::mode_breathe_cycle;
        break;
    case PROTOCOL::CHASER:
        this->mode = LED::mode_chaser;
        break;
    default:
        break;
    }
}
