
int count=0;
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  count++;
  delay(2000);
  digitalWrite(3,0);
Serial.println(count);
  if (count>255){count=0;}
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
  OCR0A = count;
}
