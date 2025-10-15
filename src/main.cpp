#include <Arduino.h>
#include "user.h"

void setup() {
    /* --------------------  MISC Display  --------------------*/
    Serial.begin(115200);  // Setup the serial consol

    /* --------------------  Setup Display  --------------------*/
    Button::Button btn;
    btn.init();
    /* --------------------  Setup Sensors  --------------------*/
}

void loop() {
    Serial.println("Hello");
    delay(1000);
}
