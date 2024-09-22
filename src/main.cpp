#include <Arduino.h>

#include <cam.h>

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.setDebugOutput(true);

    initCamera();

    pinMode(LED_GPIO_NUM, OUTPUT);
}

void loop() {
    digitalWrite(LED_GPIO_NUM, HIGH);
    delay(500);
    digitalWrite(LED_GPIO_NUM, LOW);
    delay(500);
}