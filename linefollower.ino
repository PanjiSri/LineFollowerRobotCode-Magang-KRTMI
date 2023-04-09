//Import library
#include <math.h>

//Pendefinisian nomor pin untuk dihibungkan dengan pin OUT pada IR sensor
#define IR_Sensor1 /*No Pin*/  
#define IR_Sensor2 /*No Pin*/  
#define IR_Sensor3 /*NO Pin*/  

//Deklarasi untuk motor A 
int motor1Pin1 = /*No Pin*/;
int motor1Pin2 = /*No Pin*/;
int enable1Pin = /*No Pin*/; //IInput Ini buat on off si motor B, kalau dikasih HIGH, motor bisa dikendaliin

//Deklarasi untuk motor B
int motor2Pin1 = /*No Pin*/;
int motor2Pin2 = /*No Pin*/;
int enable2Pin = /*No Pin*/; //IInput Ini buat on off si motor B, kalau dikasih HIGH, motor bisa dikendaliin 

//Deklarasi variabel untuk menyimpan kondisi sensor
int IR1; 
int IR2;
int IR3;

//Pendefinisian nomor pin untuk encoder
#define encoder1A /*No Pin*/
#define encoder1B /*No Pin*/
#define encoder2A /*No Pin*/
#define encoder2B /*No Pin*/

//Deklarasi untuk encoder
long encoder1Position = 0;
long encoder2Position = 0;
float rpm,speed;
int interval=100;
unsigned int time,newTime;

//Deklarasi untuk position
float positionX = 0;
float positionY = 0;
float degrees = 0;
float newDegrees;

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_Sensor1, INPUT); //Pin didefinisikan sebagai input dari sensor 1
  pinMode(IR_Sensor2, INPUT); 
  pinMode(IR_Sensor3, INPUT);

  pinMode(encoder1A, INPUT);
  pinMode(encoder1B, INPUT);
  pinMode(encoder2A, INPUT);
  pinMode(encoder2B, INPUT);
  attachInterrupt(/*No Pin Encoder*/, trigger1Encoder, CHANGE);
  attachInterrupt(/*No Pin Encoder*/, trigger2Encoder, CHANGE);
  Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  IR1=digitalRead(IR_Sensor1)                           //Memasukkan kondisi sensor1 ke variabel IR1
  IR2=digitalRead(IR_Sensor2)
  IR3=digitalRead(IR_Sensor3)
  if(IR1==HIGH && IR2==LOW && IR3==HIGH){                //Seandainya hanya sensor tengah yang mendeteksi garis
    //Buat program untuk mengatur robot agar bergerak maju
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  }   
  else if (IR1==HIGH && IR2==HIGH && IR3==LOW){          //Seandainya hanya sensor kanan yang mendeteksi garis
    //Buat program untuk mengatur robot agar bergerak ke kanan
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
  }
  else if (IR1==LOW && IR2==HIGH && IR3==HIGH){         //Seandainya hanya sensor kiri yang mendeteksi garis  
    //Buat program untuk mengatur robot agar bergerak ke kiri
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);    
  }
  else if (IR1==HIGH && IR2==HIGH && IR3==HIGH){        //Seandainya gak ada sensor yang mendeteksi garis
    //Buat program motor biar berhenti gerak
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);   
        
  }

  newtime=millis();
  if (newTime - time >= interval){
    //Program mencari kecepatan robot
    rpm1 = (encoder1Position/330)/0.001666667;
    speed1 = (2 * 3.14 * rpm1 * r/*Jari jari roda*/)/60;
    rpm2 = (encoder2Position/330)/0.001666667;
    speed2 = (2 * 3.14 * rpm2 * r/*Jari jari roda*/)/60;
    speed = (speed1 + speed2)/2;
    time = newTime;
    encoder1Position = 0;
    encoder2Position = 0;

    //Mengetahui sudut robot
    newDegrees = degrees + (/*wheel radius*/ * (speed2 - speed1)/(2 * /*jarak roda ke center*/))
    degrees = newDegrees

    //Posisi terhadap X
    positionX = positionX + speed * cos(degrees)
    //Posisi terhadap Y
    positionY = positionY + speed * sin(degrees)
  }

}

void trigger1Encoder(){
  if (digitalRead(encoder1A)==digitalRead(encoder1B)){
    encoder1Position--;
  }else{
    encoder1Position++;
  }
}

void trigger2Encoder(){
  if (digitalRead(encoder2A)==digitalRead(encoder2B)){
    encoder2Position--;
  }else{
    encoder2Position++;
  }
}