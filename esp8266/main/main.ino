#include "include/led_controller.hpp"

LED::Controller *controller = 0;

void setup()
{
    // Create the LED Controller object
    controller = new LED::Controller(300);
    
}
void loop()
{

}