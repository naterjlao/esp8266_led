#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <user_interface.h>

const char* ssid = "lao-mesh";
const char* passwd = "11531Seneca!";

WiFiUDP udp;
unsigned int m_port = 4000;
IPAddress m_ip(239,1,1,1);

char input_buffer[4096];

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(NONE_SLEEP_T); // reference https://arduino.stackexchange.com/questions/39957/esp8266-udp-multicast-doesnt-receive-packets
    WiFi.setOutputPower(0);
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
}

void loop()
{
    int length = udp.parsePacket();
    if (length > 0)
    {
        Serial.print("received packet of size ");
        Serial.println(length);
    }
}