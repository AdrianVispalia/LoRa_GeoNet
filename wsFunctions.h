#ifndef _WS_H
#define _WS_H

#include "geom.h"
#include "wsPacketFormatter.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "webserver.h"
#include "loraFunctions.h"


AsyncWebSocket ws("/ws");
point localPos = { .x = 0, .y = 0, .z = 0 };


void handleWsMsg(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        if (!checkWsPacketFormat((char*)data)) return;

        int type = data[0];
        if (type != (int)GPS_MSG && type != (int)TXT_MSG) { // TODO: change later
            displayString("Unknown msg: " + String((char*)data), 2000);
        }
        if (type == (int)TXT_MSG) {
            String wsPacket = (char*)data;
            ws.textAll(wsPacket.c_str());

            String recv_msg_author = String(getWsPacketAuthor(wsPacket.c_str()));
            String recv_msg_content = String(getWsPacketContent(wsPacket.c_str()));
            String recv_msg = "WS msg: " + recv_msg_author + "| " + recv_msg_content;
            displayString(recv_msg, 10);

            uint8_t tmpBuffer[MAX_LORA_PACKET_SIZE];
            size_t tmpBufferLength = getNewLoraPacket(
                getCoordinates(localPos),
                getWsPacketCoords(wsPacket.c_str()),
                getWsPacketAuthor(wsPacket.c_str()),
                getWsPacketContent(wsPacket.c_str()),
                &tmpBuffer[0]
            );
            transmitLoRaPacket(&tmpBuffer[0], tmpBufferLength);
        }
        if (type == (int)GPS_MSG) {
            localPos = getCartesianPoint(getWsPacketCoords((char*)data));
        }
    }
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            handleWsMsg(arg, data, len);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void initWebSocket() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
}

#endif
