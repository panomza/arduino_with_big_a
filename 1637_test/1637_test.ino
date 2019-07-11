
#include "TM1637.h"

//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//0~9,A,b,C,d,E,F
 

 
#define dht_pin 2 // Pin sensor is connected to
#define CLK 3//Pins for TM1637       
#define DIO 4
 
TM1637 tm1637(CLK,DIO);

 

void setup(){
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); 
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
 
  delay(1500);//Delay to let system boot

 
}//end "setup()"
 

 
void loop(){
 
  //Start of Program 
 
  DHT.read11(dht_pin);
 


    tm1637.display(1,123); 
    tm1637.display(2,456);
    tm1637.display(3,12);  // put a C at the end
    
    delay (3000);
    
    tm1637.display(1,23); 
    tm1637.display(2,454); 
    tm1637.display(3,789);

    
  //Wait 3 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
    delay(3000);
 
}// end loop() 
