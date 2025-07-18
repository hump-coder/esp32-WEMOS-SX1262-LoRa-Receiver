#include "config.h"
#include "Arduino.h"

#include "receiver.h"
#include "battery.h"


Device *device = 0;
// Display display;
Battery battery;

void setup() {

    
    Serial.begin(115200);
    Serial.println("-------------------------------------------");
    Serial.println("Setting up");

    // display.setup();
    battery.setup();


    device = new Receiver(battery);

    
    device->setup();
    Serial.println("Setup complete");
    Serial.println("-------------------------------------------");
}


void loop() {
    
    device->loop();
    // display.loop();
}

