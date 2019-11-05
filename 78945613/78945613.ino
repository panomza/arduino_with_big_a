float p=0;
float f=0;


void setup() {
  Serial.begin(9600);
  pinMode(14,INPUT);
  pinMode(3,OUTPUT);
}

void loop() {
 p = analogRead(14);
 f = (p*0.0048875855);
  Serial.println(f);
  
}
