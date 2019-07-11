int rrr=0;
void setup() {
  Serial.begin(9600);
pinMode(21,INPUT);
}

void loop() {
  rrr=digitalRead(21);
  Serial.println(rrr);
}
