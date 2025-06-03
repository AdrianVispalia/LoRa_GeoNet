#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WiFiClientSecure.h>
#include "pageHtml.h"
#include "iconXml.h"
#include "secrets.h"


AsyncWebServer server(80);
static DNSServer dnsServer;


String textProcessor(const String& var){
    //Serial.println(var); // TODO: check if erasable
    // if(var == "STATE") { if (ledState) { return "ON"; } else { return "OFF"; } }
    return String();
}


class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    bool canHandle(__unused AsyncWebServerRequest *request) const override {
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      String redirectUrl = String("http://") + String(WiFi.softAPIP().toString().c_str()) + String("/");
      request->redirect(redirectUrl);
    }
};


void setupWebServer() {
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.printf("AP station device's IP: %s\n", WiFi.softAPIP().toString().c_str());
    displayString(String(WiFi.softAPIP()), 500);

    dnsServer.start(53, "*", WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/html", index_html, textProcessor);
    });
    server.on("/Telegram_Logo.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "image/svg+xml", icon_xml, textProcessor);
    });
    server.addHandler(new CaptiveRequestHandler());
    server.begin();
}

#endif
