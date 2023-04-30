  //Pendefinisian nomor pin untuk dihibungkan dengan pin OUT pada IR sensor
  #include <Arduino.h>
  #include <math.h>
  #include <WiFi.h>
  #include <PubSubClient.h>

  #define IR_Sensor1 21
  #define IR_Sensor2 22
  #define IR_Sensor3 23 
  #define IR_Sensor4 35
  #define IR_Sensor5 34

 // #define encoder1A 5
 // #define encoder1B 5
 // #define encoder2A 5
 // #define encoder2B 5

  //Deklarasi untuk encoder
  long encoder1Position = 0;
  long encoder2Position = 0;
  float rpm;
  float rpm1;
  float rpm2;
  float speed;
  float speed1;
  float speed2;
  int interval=100;
  unsigned long currentTime = 0;
  unsigned long newTime; 
  String gerak;

  //Deklarasi untuk position
  float positionX = 0;
  float positionY = 0;
  float degrees = 0;
  float newDegrees;

  //Deklarasi untuk motor A 
  int motor1Pin1 = 5;
  int motor1Pin2 = 18;
  int enable1Pin = 19; //IInput Ini buat on off si motor B, kalau dikasih HIGH, motor bisa dikendaliin
  int motor2Pin1 = 2;
  int motor2Pin2 = 4;
  int enable2Pin = 15; //IInput Ini buat on off si motor B, kalau dikasih HIGH, motor bisa dikendaliin 
  char message[50];

  //Deklarasi variabel untuk menyimpan kondisi sensor
  int IR1; 
  int IR2;
  int IR3;
  int IR4;
  int IR5;

 /* //Deklarasi buat MQTT
  const char* ssid = "ganti SSID";
  const char* password = "ganti dengan password";
  const char* mqtt_server = "alamat MQTT broker";
  const int mqtt_port = 1883;
  //const char* mqtt_username = "MQTT username";
  //const char* mqtt_password = "MQTT password";

  //bagian terkait MQTT
  WiFiClient wifiClient;
  PubSubClient client(wifiClient); */



  void setup() {

    Serial.begin(9600);

    //WiFi.begin(ssid, password);
/*    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    client.setServer(mqtt_server, mqtt_port);
    while (!client.connected()) {
      Serial.println("Connecting to MQTT...");
      if (client.connect("arduino_client")){
        Serial.println("Connected to MQTT");       
      } else{
        Serial.println("Gagal terhubung");
        Serial.println(client.state());
        delay(2000);      
      }
               
    }*/

    //Menyalakan motor
    // put your setup code here, to run once:
    // Inisialisasi IR Sensor
    pinMode(IR_Sensor1, INPUT); //Pin didefinisikan sebagai input dari sensor 1
    pinMode(IR_Sensor2, INPUT); 
    pinMode(IR_Sensor3, INPUT);
    pinMode(IR_Sensor4, INPUT);
    pinMode(IR_Sensor5, INPUT); 
    
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    //attachInterrupt(/*1a*/ , trigger1Encoder, CHANGE);
    //attachInterrupt(/*2a*/, trigger2Encoder, CHANGE);


  }


/*  void trigger1Encoder(){
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
*/

  void loop(){
    analogWrite(enable2Pin, 150);
    analogWrite(enable1Pin, 150);
    // put your main code here, to run repeatedly:
    IR1=digitalRead(IR_Sensor1);                          //Memasukkan kondisi sensor1 ke variabel IR1
    IR2=digitalRead(IR_Sensor2);
    IR3=digitalRead(IR_Sensor3);
    IR4=digitalRead(IR_Sensor4);
    IR5=digitalRead(IR_Sensor5);

    // Bergerak Maju  
    if(IR1==LOW && IR2==HIGH && IR3==HIGH && IR4 == HIGH && IR5 == LOW){   

      
      //Buat program untuk mengatur robot agar bergerak maju
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      Serial.println("Bergerak Lurus 1");
      gerak = "Bergerak lurus 1";
      
    }   
    // Bergerak lurus
    else if (IR1 == LOW && IR2 == LOW && IR3 == HIGH && IR4 == LOW && IR5 == LOW){          
      //Buat program untuk mengatur robot agar bergerak lurus
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      Serial.println("Bergerak lurus 2");
      gerak = "Bergerak lurus 2";
    }

    // Berhenti
    else if (IR1 == LOW && IR2 == LOW && IR3 == LOW && IR4 == LOW && IR5 == LOW){  
      analogWrite(enable2Pin, 110);
      analogWrite(enable1Pin, 110);        
    
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);    
      Serial.println("Berhenti 1");
      gerak = "Berhenti 1";
      delay(0);
    }
    // Bergerak kanan
    else if (IR1 == LOW && IR2 == HIGH && IR3 == HIGH && IR4 == HIGH && IR5 == HIGH){    
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);
                
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);   
      Serial.println("Bergerak ke arah kanan 1");
      gerak = "Bergerak ke arah kanan 1";
      delay(0);
          
    }
    // Bergerak kanan
    else if (IR1 == LOW && IR2 == LOW && IR3 == HIGH && IR4 == HIGH && IR5 == HIGH){   
    analogWrite(enable2Pin, 170);
    analogWrite(enable1Pin, 170);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);   
    Serial.println("Bergerak ke arah kanan 2");
    gerak = "Bergerak ke arah kanan 2";
    delay(0);
          
    }
    // Bergerak kanan
    else if (IR1 == LOW && IR2 == LOW && IR3 == LOW && IR4 == HIGH && IR5 == HIGH){     
    analogWrite(enable2Pin, 170);
    analogWrite(enable1Pin, 170);   
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);   
    Serial.println("Bergerak ke arah kanan 3");
    gerak = "Bergerak ke arah kanan 3";
    delay(0);
          
    }
    // Bergerak kanan
    else if (IR1 == LOW && IR2 == LOW && IR3 == LOW && IR4 == LOW && IR5 == HIGH){        
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170); 
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);   
      Serial.println("Bergerak ke arah kanan 4");
      gerak = "Bergerak ke arah kanan 4";
      delay(0);
          
    }
    else if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH && IR4 == HIGH && IR5 == LOW){  
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);           
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);   
      Serial.println("Bergerak ke arah kiri 1");
      gerak = "Bergerak ke arah kiri 1";
      delay(0);
          
    }
    else if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH && IR4 == LOW && IR5 == LOW){    
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);     
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);   
      Serial.println("Bergerak ke arah kiri 2");
      gerak = "Bergerak ke arah kiri 2";
      delay(0);
          
    }
    else if (IR1 == HIGH && IR2 == HIGH && IR3 == LOW && IR4 == LOW && IR5 == LOW){ 
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);        
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);   
      Serial.println("Bergerak ke arah kiri 3");
      gerak = "Bergerak ke arah kiri 3";
      delay(0);
      
          
    }
    else if (IR1 == HIGH && IR2 == LOW && IR3 == LOW && IR4 == LOW && IR5 == LOW){     
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);    
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);   
      Serial.println("Bergerak ke arah kiri 4");
      gerak = "Bergerak ke arah kiri 4";
      delay(0);
          
    }
    /*else if (IR1 == HIGH && IR2 == HIGH && IR3 == HIGH && IR4 == HIGH && IR5 == HIGH){        
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);   
      Serial.println("Berhenti 2");
      gerak = "Berhenti 2";
      delay(0);*/
          
    //}
    else if (IR1 == LOW && IR2 == HIGH && IR3 == LOW && IR4 == LOW && IR5 == LOW){  
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);       
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);   
      Serial.println("kiri revisi");
      gerak = "kanan revisi";
      delay(200);
    }
    else if (IR1 == LOW && IR2 == LOW && IR3 == LOW && IR4 == HIGH && IR5 == LOW){  
      analogWrite(enable2Pin, 170);
      analogWrite(enable1Pin, 170);       
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);   
      Serial.println("kanan revisi");
      gerak = "kiri revisi";
      delay(200);      
    }  
    


    /*newTime=millis();
    if (newTime - currentTime >= interval){
      //Program mencari kecepatan robot
      rpm1 = (encoder1Position/330.0)/0.001666667;
      speed1 = (3.14 * rpm1 * 0.084 )/60.0;
      rpm2 = (encoder2Position/330.0)/0.001666667;
      speed2 = (3.14 * rpm2 * 0.084)/60.0;
      speed = (speed1 + speed2)/2.0;
      currentTime = newTime;
      encoder1Position = 0;
      encoder2Position = 0;


      //Mengetahui sudut robot 
      newDegrees = degrees + ( 0.042 * (speed2 - speed1)/(2 * (0.172/2)));
      degrees = newDegrees;

      //Posisi terhadap X
      positionX = positionX + speed * cos(degrees);
      //Posisi terhadap Y
      positionY = positionY + speed * sin(degrees);

      //Mengirimkan pesan ke MQTT broker
      sprintf(message, "%.2f %.2f %s", positionX, positionY, gerak.c_str());
      client.publish("robot_pose", message);*/
      
    //}
  }
