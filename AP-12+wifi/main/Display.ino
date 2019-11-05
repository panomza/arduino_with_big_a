#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 3
#define DIO 2
TM1637Display display(CLK, DIO);


void Display(){

       display.showNumberDec(averagedust,false);
}
