#include <Arduino.h>
#include <WiFi.h>

#include "cam.h"
#include "secret.h"

// ===========================
// Enter your WiFi credentials
// ===========================
const char* wifi_ssid = WIFI_SSID;
const char* wifi_pass = WIFI_PASS;

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.setDebugOutput(true);

    initCamera();

    WiFi.begin(wifi_ssid, wifi_pass);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    
    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");

    pinMode(LED_GPIO_NUM, OUTPUT);
}

void loop() {
    digitalWrite(LED_GPIO_NUM, HIGH);
    delay(500);
    digitalWrite(LED_GPIO_NUM, LOW);
    delay(500);
}