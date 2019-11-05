
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FS.h>

#include "DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// wifimanager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <ArduinoJson.h> 

#include <SoftwareSerial.h>
SoftwareSerial NanoSerial(0, 2); // RX | TX

//wifi variables

const char auth[] = "d7c89935fa6449caabdb6753b6d80b11";


void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// read the stupid board

char datar;

char data_bord ;
String dataj_bord;

unsigned int dust=0;
float timer=0;
unsigned int Speed=0;
unsigned int Power=0;
unsigned int Auto=0;




byte state_button = 0;

// Blynk read button and Trasfer functions///////////////////////////////////////////////////////////


int h = 0;
int t = 0;
unsigned int time_DHT = 0;


byte button=0;
byte num=10;

BLYNK_WRITE(V0) // ON-OFF
{
  while(button<num){
      NanoSerial.print("O"); 
      button++;
      Serial.println(button);
     
  } 
  button=0;   
}

BLYNK_WRITE(V1) // Speed
{
  while(button<num){
      NanoSerial.print("s"); 
      button++;
      Serial.println(button);
      ;
  } 
  button=0;           
}

BLYNK_WRITE(V3) // Timer
{
  while(button<num){
      NanoSerial.print("t"); 
      button++;
      Serial.println(button);
      
  } 
  button=0;          
}

BLYNK_WRITE(V4) //Auto
{  
   while(button<num){
      NanoSerial.print("a"); 
      button++;
     
  } 
  button=0;           
}

  /////////////// wifimanager//////////////////


void wifi(){


if (datar=='W'){
  digitalWrite(1,0);
  WiFi.disconnect();
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("Air Purifier"); 
  digitalWrite(1,1);

      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
      NanoSerial.print("w"); NanoSerial.print("w");
           
  } 
 
}


/////////////////////////////////////////////////////////////////////////////////////////////

char blynk_token[40]="";
bool shouldSaveConfig = false;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup()
{

  Serial.begin(9600);

  dht.begin();
  
   
 SPIFFS.begin();

 //read configuration from FS json
  Serial.println("mounting FS...");
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
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(blynk_token, json["blynk_token"]);
         

        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  
  WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 33);
  WiFiManager wifiManager;  
  wifiManager.setSaveConfigCallback(saveConfigCallback); 
  wifiManager.addParameter(&custom_blynk_token);




  if (!wifiManager.autoConnect("Smart")) {
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
    
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
  }



  /////////////////////////////////Send data////////////////////////////////////
  
//  pinMode(D2, INPUT);
//  pinMode(D3, OUTPUT);
  
  pinMode(2, INPUT);
  pinMode(0, OUTPUT);
  
  pinMode(3, INPUT);
  pinMode(1, OUTPUT);

  NanoSerial.begin(57600);

//  digitalWrite(1,0);
  
}





void loop()
{
  Blynk.run();
  
//  receive_bord();
  
  Sensor_DHT();

  wifi();

}
