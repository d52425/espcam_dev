#include <Arduino.h>

#include "esp_camera.h"
#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM
#include "camera_pins.h"

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.setDebugOutput(true);

    pinMode(LED_GPIO_NUM, OUTPUT);
}

void loop() {
    digitalWrite(LED_GPIO_NUM, HIGH);
    delay(500);
    digitalWrite(LED_GPIO_NUM, LOW);
    delay(500);
}