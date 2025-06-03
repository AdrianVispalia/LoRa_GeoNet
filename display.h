#ifndef _OLED_DISPLAY_H
#define _OLED_DISPLAY_H

#include <Wire.h>
#include "SSD1306Wire.h"
#include "QRCodeGenerator.h"
#include "secrets.h"
#include "board_def.h"


OLED_CLASS_OBJ display(OLED_ADDRESS, OLED_SDA, OLED_SCL);


void setupDisplay() {
  if (OLED_RST > 0) {
    pinMode(OLED_RST, OUTPUT);
    for (int i = 0; i < 3; i++) {
        digitalWrite(OLED_RST, i % 2 == 0 ? HIGH : LOW);
        delay(100);
    }
  }

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
}

void displayString(String text, int delayTime) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2, text);
  display.display();
  Serial.println("displayString: " + text);
  delay(delayTime);
}

void printWiFiQrCode() {
  display.clear();
  int height = display.getHeight();
  int width = display.getWidth();
  int startWidth = (width - height) / 2;

  String wifiQRText = "WIFI:T:WPA;S:" + String(AP_SSID) + ";P:" + String(AP_PASSWORD) + ";;\n\0";
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, wifiQRText.c_str());
  
  if (qrcode.size * 2 > height) {
    Serial.println("QR code too big!!!");
    return;
  }

  for (int16_t x = startWidth; x < startWidth + qrcode.size * 2; x++) {
    for (int16_t y = 0; y < qrcode.size * 2; y++) {
      if (qrcode_getModule(&qrcode, (x - startWidth) / 2, y / 2)) {
        display.setPixel(x, y);
      }
    }
  }
  display.display();
  delay(500);
}

#endif
