// UDP Ethernet Libraries
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <user_interface.h>
#include "include/protocol.hpp"

// LED Controller Libraries
#include <FastLED.h>
#include "include/led_controller.hpp"

// UDP Ethernet Variables
/// @note TOP SECRET
const char *ssid = "REDACTED";
const char *passwd = "REDACTED";
WiFiUDP udp;

// UDP Multicast Receive on 239.1.1.1:4000
IPAddress m_ip(239, 1, 1, 1);
unsigned int m_port = 4000;
/// @note this is more than necessary...
char input_buffer[1024];
static bool setup_wifi();

// LED Controller Variables
#define NUM_LEDS 139
LED::Controller *controller = 0;

// ----- MAIN FUNCTION IMPLEMENTATION ----- //

/// @brief
void setup()
{
    // Serial output
    /// @todo may be removed in future
    Serial.begin(115200);
    Serial.println();

    /// @todo consider indicating red if WiFi configuration failed
    bool wifi_status = setup_wifi();

    // Create the LED Controller object
    controller = new LED::Controller(NUM_LEDS);
}

/// @brief
void loop()
{
    // Receive UDP payloads
    PROTOCOL::PAYLOAD payload;
    if ((udp.parsePacket() == sizeof(payload)) && (udp.read((char *)&payload, sizeof(payload)) > 0))
    {
        controller->receive(payload);
        memset(&payload, 0, sizeof(payload));
    }

    // Render LED Frame
    controller->render();
}

// ----- PRIVATE FUNCTION IMPLEMENTATION ----- //

/// @brief Configures WiFi setttings for the ESP8266
/// @return
static bool setup_wifi()
{
    bool status = true;

    // Setup network configuration
    WiFi.mode(WIFI_STA);               // Station Mode (network client)
    wifi_set_sleep_type(NONE_SLEEP_T); // reference https://arduino.stackexchange.com/questions/39957/esp8266-udp-multicast-doesnt-receive-packets
    WiFi.setOutputPower(0);            // Set WiFi output power to off - only receive

    // Connect to network
    WiFi.begin(ssid, passwd);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connnection Successful");
    Serial.print("IP ADDRESS: ");
    Serial.println(WiFi.localIP());

    // Setup UDP Multicast Configuration
    if (udp.beginMulticast(WiFi.localIP(), m_ip, m_port))
    {
        Serial.println("Multicast Configuration Successful");
        Serial.print("UDP MULTICAST ADDRESS: ");
        Serial.println(m_ip);
        Serial.print("UDP MULTICAST PORT: ");
        Serial.println(m_port);
    }
    else
    {
        Serial.println("Multicast Configuration Failed");
    }

    return status;
}
