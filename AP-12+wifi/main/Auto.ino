
void Auto(){

    mcp.digitalWrite(AUTO,stateA);
    
    if(currenttime-autotime>6000 && stateA==1){
        Serial.println("Auto");
        
        if(averagedust>=40){
           clearspeed();
           digitalWrite(M4,1);
           }else 
        if(averagedust>=30){
           clearspeed();
           digitalWrite(M3,1);
           }else 
        if(averagedust>=20){
           clearspeed();
           digitalWrite(M2,1);
           }else{
           clearspeed();
           digitalWrite(M1,1);
           }
        
        autotime=currenttime;
        applythespeedswitch();
    }
}
