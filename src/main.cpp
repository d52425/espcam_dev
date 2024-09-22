#include <Arduino.h>
#include <WiFi.h>

#include "cam.h"

#include "esp_http_server.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===========================
// Enter your WiFi credentials
// ===========================
const char* wifi_ssid = "WIFI_SSID";
const char* wifi_pass = "WIFI_PASS";

httpd_handle_t stream_httpd = NULL;

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.setDebugOutput(true);

    initCamera();

/*
    WiFi.begin(wifi_ssid, wifi_pass);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
*/  
    pinMode(LED_GPIO_NUM, OUTPUT);

    Wire.begin(D9, D10);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for(;;) {
            Serial.println(F("SSD1306 allocation failed"));
            delay(1000); // Don't proceed, loop forever
        }
    }
    display.display();

}

void loop() {
    digitalWrite(LED_GPIO_NUM, HIGH);
    delay(100);
    digitalWrite(LED_GPIO_NUM, LOW);
    delay(100);

    Serial.println("esp_camera_fb_get()");
    // camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Failed to get camera frame buffer");
        return;
    }
    // 画面表示をクリア
    display.fillScreen(BLACK);

    int8_t bmp[96*96];
    for(uint16_t h = 0; h < 96; h++) {
        for(uint16_t w = 0; w < 96; w++) {
            u8_t c = *(fb->buf + (h+w*96));
            // Serial.println(c);
            if(c < 127) {
                display.drawPixel(w, 96-h, BLACK);
            } else {
                display.drawPixel(w, 96-h, WHITE);
            }
        }
    }

    //ビットマップの表示
    // display.drawBitmap(0, 0, fb->buf, 96, 96, WHITE);

    // 描画バッファの内容を画面に表示
    display.display();

    esp_camera_fb_return(fb);
    
}