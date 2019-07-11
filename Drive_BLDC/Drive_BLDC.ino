int button      = 14;
bool Bs         = 1;                   // speed input state
bool Ls         = 1;                   // previous speed input state
bool stateS     = 0;         // speed state
unsigned short int index = 0;                // case counter
short int speedt0;
int buttondelay =0;
unsigned int currenttime=0;

int OUT=9;

int M1  = 2;
int M2  = 3;
int M3  = 4;
int M4  = 5;
int M5  = 6;
int M6  = 7;
int M7  = 8;
int M8  = 10;
int M9  = 11;
int M10 = 12;
int power= 13;

void clearspeed(){
      
      digitalWrite(M1,0);  
      digitalWrite(M2,0);
      digitalWrite(M3,0);
      digitalWrite(M4,0);
      digitalWrite(M5,0);  
      digitalWrite(M6,0);
      digitalWrite(M7,0);
      digitalWrite(M8,0);
      digitalWrite(M9,0);
      digitalWrite(M10,0);
}


void setup() {
  Serial.begin(9600);
pinMode(OUT,OUTPUT);
pinMode(button,INPUT);

int outputpins[12] = {
   M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,OUT,power
  };
  for(int j=0;j< sizeof(outputpins)/sizeof(1);j++){
    pinMode(outputpins[j],OUTPUT);
  }
  index = 0;
}

void loop() {
  
currenttime=millis();
Bs=digitalRead(button);

  

 if ((Bs != Ls) && (Bs == 0)&& (currenttime-speedt0 > buttondelay)){  
     Ls=Bs;
     index++;
     speedt0=currenttime;            
     if(index>6){index=0;}
     Serial.print("Speed is : ");
     Serial.println(index);
 }
 else if ((Bs != Ls) && (Bs == 1)&& (currenttime-speedt0 > buttondelay)){
    Ls=Bs;
  }
  
 if (index>0){digitalWrite(power,1); digitalWrite(M7,1);}
 if (index==0){digitalWrite(M7,0);}
 
switch (index) {
    case 0:
      clearspeed();
      digitalWrite(power,0);
      noTone(OUT); 
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,1);
      tone(OUT,125);   
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,1);
      tone(OUT,200);
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,1);
      tone(OUT,250);
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,1);
      tone(OUT,300);
      break;
    case 5:
      clearspeed();
      digitalWrite(M5,1);
      tone(OUT,400);
      break;
    case 6:
      clearspeed();
      digitalWrite(M6,1);   
      tone(OUT,450);
      break;

  
  }

  
}
