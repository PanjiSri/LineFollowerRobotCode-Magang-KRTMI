#define IR_Sensor 7

int IR1;

void setup() {
  pinMode(IR_Sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  IR1 = digitalRead(IR_Sensor);
  if (IR1 == HIGH) {
    Serial.println("Garis hitam");
    // Do something here when a black line is detected, such as stopping a robot or changing its direction
  }
  delay(100); // add a small delay to avoid flooding the serial output with repeated messages
}
