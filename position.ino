//Import library
#include <Arduino.h>
#include <math.h>
#include <WiFi.h>
#include <PubSubClient.h>

#Deklarasi Pin Motor
#define LEFT_MOTOR_PIN //ganti nomor Pin
#define RIGHT_MOTOR_PIN //ganti nomor Pin
#define LEFT_PS_PIN //ganti nomor Pin
#define RIGHT_PS_PIN //ganti nomor pin

#define timestep 64
#define max_speed 6.28

//Deklarasi buat MQTT
const char* ssid = "ganti SSID";
const char* password = "ganti dengan password";
const char* mqtt_server = "alamat MQTT broker";
const int mqtt_port = 1883;
const char* mqtt_username = "MQTT username";
const char* mqtt_password = "MQTT password";

//Deklarasi buat kebutuhan mencari lokasi robot
float left_ps_val, right_ps_val;
float ps_values[2], dist_values[2];
float wheel_radius = 0.025;
float distance_between_wheels = 0.09;
float wheel_cirum = 2 * 3.14 * wheel_radius;
float encoder_unit = wheel_cirum / 6.28;
float robot_pose[3] = {0,0,0};
float last_ps_values[2] = {0,0};

//bagian terkait MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  
  //Inisialisasi buat MQTT
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("arduino_client", mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
 
  //Inisialisasi Pin
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(LEFT_PS_PIN, INPUT);
  pinMode(RIGHT_PS_PIN, INPUT);
}

void loop() {
  //pembacaan sensor
  ps_values[0] = analogRead(LEFT_PS_PIN);
  ps_values[1] = analogRead(RIGHT_PS_PIN);
  
  //update posisi robot ke serial monitor
  Serial.println("-----------------------------");
  Serial.print("position sensor values: ");
  Serial.print(ps_values[0]);
  Serial.print(" ");
  Serial.println(ps_values[1]);
  
  //ngitung jarak tempuh masing-masing roda
  for (int ind=0; ind<2; ind++) {
    float diff = ps_values[ind] - last_ps_values[ind];
    if (diff < 0.001) {
      diff = 0;
    }
    dist_values[ind] = diff*encoder_unit;
    last_ps_values[ind] = ps_values[ind]; // Ini tuh buat nyimpen nilai di iterasi berikutnya
  }
  
  //buat ngitung kecepatan linear sama angular
  float v = (dist_values[0]+dist_values[1])/2.0;
  float w = (dist_values[0]-dist_values[1])/distance_between_wheels;   
  
  //update posisi robot
  float dt = timestep / 1000.0; // timestep diconvert ke second, biar lebih akurat niatnya, aman kah?
  robot_pose[2] += w * dt;
  float vx = v * cos(robot_pose[2]);
  float vy = v * sin(robot_pose[2]);
  robot_pose[0] += vx * dt;
  robot_pose[1] += vy * dt;
  
  //Mengirimkan pesan ke MQTT broker
  char message[50];
  sprintf(message, "%.2f %.2f %.2f", robot_pose[0], robot_pose[1], robot_pose[2]);
  client.publish("robot_pose", message);

  //update posisi ke serial monitor
  Serial.print("robot_pose: ");
  Serial.print(robot_pose[0]);
  Serial.print(" ");
  Serial.println(robot_pose[1]);
  
  //menyalakan motor
  digitalWrite(LEFT_MOTOR_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN, HIGH);
  
  //Jeda  waktu buat loop
  delay(timestep);
}
