#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ESP8266mDNS.h>

#ifndef APSSID
#define APSSID "WHID"
#define APPSK  "Keyboard"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

MDNSResponder mdns;
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name = "viewport" content = "width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
  <title>Test Teclado</title>
  <style>
    "body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }"
  </style>
  <script>
    var websock;
    function start() {
      websock = new WebSocket('ws://' + window.location.hostname + ':81/');
      websock.onopen = function(evt) { console.log('websock open'); };
      websock.onclose = function(evt) { console.log('websock closed from server'); };
      websock.onerror = function(evt) { console.log(evt); };
      websock.onmessage = function(evt) {
        console.log(evt);
      };
      var el = document.getElementById("input"); 
      el.addEventListener("keypress", function(event){
        websock.send(event.key);
        console.log(event.key);
      });  
    }
    function buttonclick(e) {
      console.log(e.id);
      websock.send(e.id);
    }
    function ratonclick(e) {
      console.log(e.id);
      websock.send(e.id);
    }
  </script>
</head>
<body onload="javascript:start();">
  <h1>Test Teclado</h1>
  <input id="input" autocorrect="off" spellcheck="false" autocomplete="off"/>
  <p>
    <button id="Escape"  type="button" onclick="buttonclick(this);">ESC</button>
    <button id="F1"  type="button" onclick="buttonclick(this);">F1</button>
    <button id="F2"  type="button" onclick="buttonclick(this);">F2</button>
    <button id="F3"  type="button" onclick="buttonclick(this);">F3</button>
    <button id="F4"  type="button" onclick="buttonclick(this);">F4</button>
    <button id="F5"  type="button" onclick="buttonclick(this);">F5</button>
    <button id="F6"  type="button" onclick="buttonclick(this);">F6</button>
    <button id="F7"  type="button" onclick="buttonclick(this);">F7</button>
    <button id="F8"  type="button" onclick="buttonclick(this);">F8</button>
    <button id="F9"  type="button" onclick="buttonclick(this);">F9</button>
    <button id="F10"  type="button" onclick="buttonclick(this);">F10</button>
    <button id="F11"  type="button" onclick="buttonclick(this);">F11</button>
    <button id="F12"  type="button" onclick="buttonclick(this);">F12</button>
  </p>
  <p>
    <button id="Prnt"  type="button" onclick="buttonclick(this);">Prnt</button>
    <button id="Pause"  type="button" onclick="buttonclick(this);">Pause</button>
    <button id="Delete"  type="button" onclick="buttonclick(this);">Delete</button>
    <button id="Tab"  type="button" onclick="buttonclick(this);">Tab</button>
    <button id="PageUp"  type="button" onclick="buttonclick(this);">PgUp</button>
    <button id="PageDown"  type="button" onclick="buttonclick(this);">PgDn</button>
    <button id="Meta"  type="button" onclick="buttonclick(this);">Home</button>
    <button id="End"  type="button" onclick="buttonclick(this);">End</button>
    <button id="Enter"  type="button" onclick="buttonclick(this);">Enter</button>
  </p>
  <p>Flechas
    <button id="ArrowUp"  type="button" onclick="buttonclick(this);">UP</button>
    <button id="ArrowDown"  type="button" onclick="buttonclick(this);">DOWN</button>
    <button id="ArrowLeft"  type="button" onclick="buttonclick(this);">LEFT</button>
    <button id="ArrowRight"  type="button" onclick="buttonclick(this);">RIGHT</button>
  </p>
  <p>Raton
    <button id="MouseMoveUp"  type="button" onclick="ratonclick(this);">UP</button>
    <button id="MouseMoveDown"  type="button" onclick="ratonclick(this);">DOWN</button>
    <button id="MouseMoveLeft"  type="button" onclick="ratonclick(this);">LEFT</button>
    <button id="MouseMoveRight"  type="button" onclick="ratonclick(this);">RIGHT</button>
  </p>
  <p>Click Raton
    <button id="MouseClickRIGHT"  type="button" onclick="buttonclick(this);">Click Derecho</button>
    <button id="MouseClickLEFT"  type="button" onclick="buttonclick(this);">Click Izquierdo</button>
    <button id="MouseClickMIDDLE"  type="button" onclick="buttonclick(this);">Click Central</button>
  </p>
</body>
</html>
)rawliteral";


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  switch(type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
      }
      break;
    case WStype_TEXT:
      Serial.println((const char *)payload);
      webSocket.broadcastTXT(payload, length);
      break;
    case WStype_BIN:
      hexdump(payload, length);
      webSocket.sendBIN(num, payload, length);
      break;
    case WStype_PONG:
      break;
    default:
      break;
  }
}

void handleRoot() {
  server.send_P(200, "text/html", INDEX_HTML);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.begin();
  
  if (mdns.begin("espWebSock", WiFi.localIP())) {
    mdns.addService("http", "tcp", 80);
    mdns.addService("ws", "tcp", 81);
  }
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  server.handleClient();
}
