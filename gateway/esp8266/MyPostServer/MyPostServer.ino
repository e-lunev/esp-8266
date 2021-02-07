#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = LED_BUILTIN;
const int pin = 2;

const String postForms = "<html>\
  <head>\
    <title>ESP Web Server</title>\
    <style>\
      html {font-family: Arial; display: inline-block; text-align: center;}\
      h2 {font-size: 3.0rem;}\
      p {font-size: 3.0rem;}\
      body { background-color: white; font-family: Arial, Helvetica, Sans-Serif; Color: black; }\
    </style>\
  </head>\
  <body>\
      <h2>ESP Web Server</h2>\
      <input type=\"submit\" value=\"on\">\
      <input type=\"submit\" value=\"off\">\
    </form>\
  </body>\
</html>";

void handleRoot() {
  server.send(200, "text/html", postForms);
}

void handleOn() {
    server.send(200, "text/plain", "On");
    digitalWrite(pin, HIGH);
}

void handleOff() {
    server.send(200, "text/plain", "Off");
     digitalWrite(pin, LOW);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/on", handleOn);

  server.on("/off", handleOff);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
