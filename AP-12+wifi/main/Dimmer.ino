
void Dimmer(){
  
  rundim=millis();
  
  if (timedim==0){bright7=1; mcp.digitalWrite(dim,0);}else{mcp.digitalWrite(dim,1);}
  

  
  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0  || digitalRead(Btimer)==0)
  {
   timedim = sec;
   brightdim = 7;
  }
  if(rundim-trigdim>1000&&timedim>0){
    trigdim=rundim;
    timedim=timedim-1;   
    
  }

}
