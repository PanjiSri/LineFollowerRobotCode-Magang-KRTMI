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
#define encoderA /*No Pin*/
#define encoderB /*No Pin*/

//Deklarasi untuk encoder
long encoderPosition = 0;
float rpm,speed;
int interval=100;
unsigned int time,newTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_Sensor1, INPUT); //Pin didefinisikan sebagai input dari sensor 1
  pinMode(IR_Sensor2, INPUT); 
  pinMode(IR_Sensor3, INPUT);

  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  attachInterrupt(/*No Pin Encoder*/, triggerEncoder, CHANGE);
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
    rpm = (encoderPosition/30.00)/0.001666667;
    speed = (2*3.14*rpm)/60
    time = newTime;
    encoderPosition = 0;
  }

}

void triggerEncoder(){
  if (digitalRead(encoderA)==digitalRead(encoderB)){
    encoderPosition--;
  }else{
    encoderPosition++;
  }
}