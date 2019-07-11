int led = 13;

void setup() {
 pinMode(led,OUTPUT);
}

void loop() {
analogWrite(led,5);
delayMicroseconds(10);
analogWrite(led,100);
delayMicroseconds(10);
}
