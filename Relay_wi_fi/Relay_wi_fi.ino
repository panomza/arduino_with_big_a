#include <FS.h>

#define BLYNK_PRINT Serial
#include <Ethernet.h>
#include <BlynkSimpleEsp8266.h>


//////////////////// wifimanager
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>



void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

// Blynk read button and Trasfer functions///////////////////////////////////////////////////////////


BLYNK_WRITE(V1) // ALL ON
{
  int pinValue = param.asInt();

     Serial.println("all"); 

     digitalWrite(2,0);
     digitalWrite(0,0);
     digitalWrite(4,0);
     digitalWrite(5,0);

     Blynk.virtualWrite(V2,1 ); 
     Blynk.virtualWrite(V3,1 ); 
     Blynk.virtualWrite(V4,1 ); 
     Blynk.virtualWrite(V5,1 );    
}

BLYNK_WRITE(V11) 
{
  int pinValue = param.asInt();
  
  Serial.println("all"); 
    

     digitalWrite(2,1);
     digitalWrite(0,1);
     digitalWrite(4,1);
     digitalWrite(5,1);
     
     Blynk.virtualWrite(V1,0 );
     Blynk.virtualWrite(V2,0 ); 
     Blynk.virtualWrite(V3,0 ); 
     Blynk.virtualWrite(V4,0 ); 
     Blynk.virtualWrite(V5,0 );
}

////////////////////////////////////////////////////////////////

BLYNK_WRITE(V2) // Chanal 1
{
  int pinValue = param.asInt();

     digitalWrite(2,!pinValue);
     Serial.println("1");
}

BLYNK_WRITE(V12) 
{
  int pinValue = param.asInt();
  
  Serial.println("1"); 
  digitalWrite(2,!pinValue ); 
  Blynk.virtualWrite(V2,pinValue );      
}

///////////////////////////////////////////////////////////////

BLYNK_WRITE(V3) //Chanal 2
{
  int pinValue = param.asInt();

     digitalWrite(0,!pinValue);
     Serial.println("2");
}

BLYNK_WRITE(V13) 
{
  int pinValue = param.asInt();
  
  Serial.println("2");
  digitalWrite(0,!pinValue ); 
  Blynk.virtualWrite(V3,pinValue );      
}

/////////////////////////////////////////////////////////////

BLYNK_WRITE(V4) //Chanal 3
{
  int pinValue = param.asInt();

     digitalWrite(4,!pinValue);
     Serial.println("3");
}

BLYNK_WRITE(V14) 
{
  int pinValue = param.asInt();
  
  Serial.println("3"); 
  digitalWrite(4,!pinValue ); 
  Blynk.virtualWrite(V4,pinValue );      
}

////////////////////////////////////////////////////////////

BLYNK_WRITE(V5) //Chanal 4
{
  int pinValue = param.asInt();

     digitalWrite(5,!pinValue);
     Serial.println("4");
}

BLYNK_WRITE(V15) 
{
  int pinValue = param.asInt();
  
  Serial.println("4");
  digitalWrite(5,!pinValue ); 
  Blynk.virtualWrite(V5,pinValue );      
}



/////////////////////////////////////////////////////////////////////////////////////////////

char blynk_token[40]="";
char blynk[32] = "dfk4";
bool shouldSaveConfig = false;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup()
{
  Serial.begin(9600);
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
          strcpy(blynk, json["blynk"]);

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
  }else{Serial.println("failed");}
  
   
  Blynk.config(blynk_token);

  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2,1);
  digitalWrite(0,1);
  digitalWrite(1,1);
  digitalWrite(3,1);

  
}


void loop()
{
  Blynk.run();
}
