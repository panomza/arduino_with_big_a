#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
Adafruit_MCP23017 mcp;

SoftwareSerial NodeSerial(21, 20); // RX | TX

///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define OUTPUT_COUNT 5

long remote_key[] = {0xDF40BF, 0xDF609F, 0xDF48B7, 0xDF50AF, 0xDF708F};
const byte outputPins[OUTPUT_COUNT] = {0, 1, 2, 3, 4};
bool status1[5] = {0, 0, 0, 0, 0};
struct keypad {
  boolean state;
};
keypad output[OUTPUT_COUNT];

///////////////////////////////////////////////////////////////////////////


// input pins

const short int Bpow    = 14;    // power button input pin
const short int Bspeed  = 15;    // speed input pin
const short int Btimer  = 16;    // Timer button input pin

//output pins
      
const short int M1     = 4;       // motor output pin
const short int M2     = 5;       // motor output pin
const short int M3     = 6;       // motor output pin
const short int M4     = 7;      // motor output pin
const short int Speed    = 9;
const short int s1     = 10;       
const short int s2     = 11;       
const short int s3     = 12;       
const short int s4     = 13;
const short int AUTO   = 14;
const short int timerled = 6;
const short int h1     = 5;       
const short int h2     = 4;       
const short int h4     = 3;       
const short int h8     = 2;       
const short int filter = 1;
const short int ledwi  = 0;
const short int dim    = 8;


const short int BUZ    = 9;         // buzzer output pin

//////////////////////////////////////////////////////////////////////////
// state variables

//////////////////////power//////////////////////

bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state
byte stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed
unsigned int powert0 = 0;


/////////////////////speed////////////////////

bool Bs         = 1;           // speed input state
bool Ls         = 1;           // previous speed input state
bool speedcount = 0;
byte index = 0;                // case counter
unsigned int speedt0 = 0;

////////////////////Timer////////////////////

bool Bt         = 1;
bool Lt         = 1;
byte Settime = 0;
unsigned int timer0;
unsigned int timedown = 0;
unsigned int timerTg = 0;

unsigned int timetrig = 0;
unsigned int runtime = 0;


/////////////////Auto////////////////////

byte stateA     = 0;
unsigned int autotime = 0;


///////////////delays////////////////////

unsigned int buttondelay = 200; // delay between each button press in ms
unsigned int currenttime = 0;


//////////////dust sensor///////////////

const short int measurePin = A6;
const short int ledPower = 19;
const short int numaverage = 150; ///number of values for taking average
unsigned int count;
unsigned int dust[numaverage];
unsigned int averagedust = 0;


///////////////beep///////////////////

bool songindex = 0;
bool beepvarB = 0;
bool beepvarS = 0;
bool beepstarted = 0;
bool beepstartedS = 0;
byte beeppowervar = 0;
unsigned int beeptime = 0;
unsigned int beeptimeS = 0;
int play = 0;
int soundtime = 0;


///////////////Bright////////////////

byte bright7 = 0;
byte brightdim = 30;
unsigned int rundim=0;
unsigned int trigdim=0;
unsigned int timedim=0;
byte sec = 10 ;


char datar;


////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);
  mcp.begin();

  irrecv.enableIRIn(); // Start the receiver

  int inputpins[3] = {Bpow, Bspeed, Btimer};

  int outputled[14] = {Speed, s1, s2, s3, s4, AUTO, dim, timerled, h1 ,h2 ,h4, h8, ledwi, filter};

  for (int j = 0; j < sizeof(inputpins) / sizeof(1); j++) {
    pinMode(inputpins[j], INPUT);
  }

  for (int j = 0; j < sizeof(outputled) / sizeof(1); j++) {
    mcp.pinMode(outputled[j], OUTPUT);
    mcp.digitalWrite (outputled[j],0);
  }

  pinMode(21, INPUT);
  pinMode(20, OUTPUT);
  
  pinMode(BUZ, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(ledPower, OUTPUT);
  
 
  
  beepvarS = 1;

  clearspeed();
  cleartimer();

  NodeSerial.begin(57600);
 
}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {


  currenttime = millis();

  Dimmer();

//  beep();

  statebutton();

  Remote();

//  Display();

//  sensor_dust();

  powerset();

  speedset();

  TIMER();

  Auto();

  read_smart();

  send_smart();


}
