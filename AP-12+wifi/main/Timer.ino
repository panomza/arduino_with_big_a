unsigned int timerP  = 0;

void TIMER(){

    if(currenttime-timerP > 100 && timerTg>0){
      timerTg = timerTg-1;
      timerP = currenttime;
      Serial.println(timerTg);
    }
   
    if (digitalRead(Bspeed)==0 || digitalRead(Btimer)==0 && timerTg ==0) {
        mcp.digitalWrite(timerled,1);   
        }
    if (stateP==1 && timedim==0){ mcp.digitalWrite(timerled,0); }
     
    if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay)){
        Lt=Bt;
        Settime++;
        timer0 = currenttime;
        beepvarB=1;
        if(Settime>4){Settime=0;cleartimer();}
        selecttime();
        Serial.print("Timer to : ");
        Serial.println(Settime);
    } else 
    if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)){
        Lt=Bt;         
    }

   runtime=millis();
      
        if(runtime - timetrig >1000 && Settime > 0){
           timetrig = runtime;
           timedown=timedown-1;  
           Serial.println(timedown);         
           }

    if (timedown==40){Settime=4;selecttime();} 
    if (timedown==30){Settime=3;selecttime();} 
    if (timedown==20){Settime=2;selecttime();} 
    if (timedown==10){Settime=1;selecttime();}
    if (timedown==0 && Settime > 0){Bp=0;Settime=0;}      
}

void cleartimer(){
  
      mcp.digitalWrite(h1,0);  
      mcp.digitalWrite(h2,0);
      mcp.digitalWrite(h4,0);
      mcp.digitalWrite(h8,0);
}

void selecttime(){
  switch(Settime){
    case 0:
        cleartimer();
        timedown=0;
    break;
    case 1:
     cleartimer();
     timedown=10;
     mcp.digitalWrite(h1,1);  
    break;
    case 2:
     cleartimer();
     timedown=20;
     mcp.digitalWrite(h2,1);
    break;
    case 3:
     cleartimer();
     timedown=30;
     mcp.digitalWrite(h4,1);
    break;
    case 4:
     cleartimer();
     timedown=40;
     mcp.digitalWrite(h8,1);
    break;
  }
}
