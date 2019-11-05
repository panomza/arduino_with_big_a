#define BLYNK_PRINT Serial

#include <FS.h>

#include <DNSServer.h>

#include <WiFiManager.h>

#include <ESP8266WebServer.h>

#include <BlynkSimpleEsp8266.h>

#include <ArduinoJson.h>

#define SET_PIN 0

char blynk_token[40] = "754ba4e388b242b18abfd3d5c4XXXXX9";

bool shouldSaveConfig = false;

void saveConfigCallback () {
Serial.println("Should save config");
shouldSaveConfig = true;
}

void setup() {
Serial.begin(115200);
Serial.println();
pinMode(SET_PIN, INPUT_PULLUP);
delay(3000);

//read configuration from FS json
Serial.println("mounting FS…");
if (SPIFFS.begin()) {
Serial.println("mounted file system");
if (SPIFFS.exists("/config.json")) {
//file exists, reading and loading
Serial.println("reading config file");
File configFile = SPIFFS.open("/config.json", "r");
if (configFile) {
Serial.println("opened config file");
size_t size = configFile.size();
// Allocate a buffer to store contents of the file.
std::unique_ptr<char[]> buf(new char[size]);

configFile.readBytes(buf.get(), size);

DynamicJsonBuffer jsonBuffer;

JsonObject& json = jsonBuffer.parseObject(buf.get());

json.printTo(Serial);

if (json.success()) { Serial.println("\nparsed json"); strcpy(blynk_token, json["blynk_token"]);

} else { Serial.println("failed to load json config"); } configFile.close(); } }

} else {
Serial.println("failed to mount FS");
}

WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 32);
WiFiManager wifiManager;
wifiManager.setSaveConfigCallback(saveConfigCallback);
wifiManager.addParameter(&custom_blynk_token);

if (digitalRead(SET_PIN) == LOW) {
wifiManager.resetSettings();
}

if (!wifiManager.autoConnect("My NodeMCU")) {
Serial.println("failed to connect and hit timeout");
delay(3000);
ESP.reset();
delay(5000);
}

Serial.println("wifi connected");
strcpy(blynk_token, custom_blynk_token.getValue());

//save the custom parameters to FS
if (shouldSaveConfig) {
Serial.println("saving config");
DynamicJsonBuffer jsonBuffer; 
JsonObject& json = jsonBuffer.createObject();
json["blynk_token"] = blynk_token;

File configFile = SPIFFS.open("/config.json", "w");

if (!configFile) { Serial.println("failed to open config file for writing");

}

json.printTo(Serial);

json.printTo(configFile);

configFile.close();

}

Serial.println();
Serial.print("local ip : ");
Serial.println(WiFi.localIP());
Serial.print("Blynk Token : ");
Serial.println(blynk_token);
Blynk.config(blynk_token);

}

void loop() {
Blynk.run();
}
