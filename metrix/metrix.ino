////const int r1 = 3;
////const int c1 = 4;
////const int r2 = 5;
////const int c2 = 6;
////const int r3 = 7;
//const int c3 = 8;
//
//int pins [6] = {r1,r2,r3,c1,c2,c3};

void setup() {
  
  DDRD = B11111111; // set PORTD (digital 7~0) to outputs
  
//  for (int i = 0; i < 6; i++) { // for loop is used to configure common cathodes
//    pinMode(pins[i], OUTPUT);
//  }
}

//void clr(){
//  digitalWrite(r1,0);
//  digitalWrite(c1,1);
//  digitalWrite(r2,0);
//  digitalWrite(c2,1);
//  digitalWrite(r3,0);
//  digitalWrite(c3,1);
// 
//
//}

byte l1 = {
0b10100111
};

byte l2 = {
0b10001111
};

byte l3 = {
0b00101111
};

//byte l4 = {
//0b10001111
//};
//byte l5 = {
//0b10100111
//};
//
//byte l6 = {
//0b10001111
//};
//
//byte l7 = {
//0b10001111
//};
//
//byte l8 = {
//0b10001111
//};
//
//byte l9 = {
//0b10001111
//};


void gh (){
  PORTD=l1;

PORTD=l2;
}


int k =0;
long o =0;
long p =0;

void loop() {

//if(k==11){k=0;}
//if (millis()-o>1000){
//  k++;
//  
//  o=millis();
//}
// if(k==0){l1();l2();l4();}
//if(k==1){l1();}
//if(k==2){l2();}
//if(k==3){l3();}
//if(k==4){l4();}
//if(k==5){l5();}
//if(k==6){l6();}
//if(k==7){l7();}
//if(k==8){l8();}
//if(k==9){l9();}
//if(k==10){l9();l1();l2();l3();l4();l5();l7();}

PORTD2=0;
delay(500);
PORTD=l2;
delay(500);
PORTD=l3;
delay(500);
if(k==0){gh();}
//delay(500);





}
