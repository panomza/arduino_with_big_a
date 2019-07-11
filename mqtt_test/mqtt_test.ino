#include <ESP8266WiFi.h>
#include <PubSubClient.h>
  char data;
const char* ssid = "HTR-MK";
const char* password = "hatariled1";
const char* mqttServer = "iot.hatari.cc";
const int mqttPort = 1883;
const char* mqttUser = "YourMqttUser";
const char* mqttPassword = "YourMqttUserPassword";
const byte SWITCH_PIN = 0;           // Pin to control the light with
bool state=0;
const char* TOPIC="esp/test";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {

 pinMode(D4,OUTPUT);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message ; ");
  for (int i = 0; i < length; i++) {
    int message  ;
    Serial.print((char)payload[i]);
    data=(char)payload[i];
    }
  Serial.println();
  Serial.println("-------------------------");
  Serial.println(data);
 if (data=='o'){
  digitalWrite(D4,0);
 
}else{digitalWrite(D4,1);}

 if (data=='p'){
  digitalWrite(D4,0);
  delay(500);
  digitalWrite(D4,1);
  delay(500);
  digitalWrite(D4,0);
  delay(500);
  digitalWrite(D4,1);
  delay(500);
  digitalWrite(D4,0);
  delay(500);
  digitalWrite(D4,1);
  delay(500);
}
}
void loop() {
  client.loop();
 

  if(digitalRead(SWITCH_PIN) == 0) 
  {
    state = !state; //toggle state
    if(state == 1) // ON
    {
      client.publish(TOPIC, "o");
    }
    else // OFF
    {
      client.publish(TOPIC, "p");
    }

    while(digitalRead(SWITCH_PIN) == 0) // Wait for switch to be released
    {
      // Let the ESP handle some behind the scenes stuff if it needs to
      yield(); 
    }
  }
}
