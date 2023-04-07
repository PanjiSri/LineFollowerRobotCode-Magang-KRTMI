#include <Arduino.h>
#include <math.h>

#define LEFT_MOTOR_PIN 12
#define RIGHT_MOTOR_PIN 13
#define LEFT_PS_PIN 34
#define RIGHT_PS_PIN 35

#define timestep 64
#define max_speed 6.28

float left_ps_val, right_ps_val;
float ps_values[2], dist_values[2];
float wheel_radius = 0.025;
float distance_between_wheels = 0.09;
float wheel_cirum = 2 * 3.14 * wheel_radius;
float encoder_unit = wheel_cirum / 6.28;
float robot_pose[3] = {0,0,0};
float last_ps_values[2] = {0,0};

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(LEFT_PS_PIN, INPUT);
  pinMode(RIGHT_PS_PIN, INPUT);
}

void loop() {
  ps_values[0] = analogRead(LEFT_PS_PIN);
  ps_values[1] = analogRead(RIGHT_PS_PIN);

  Serial.println("-----------------------------");
  Serial.print("position sensor values: ");
  Serial.print(ps_values[0]);
  Serial.print(" ");
  Serial.println(ps_values[1]);

  for (int ind=0; ind<2; ind++) {
    float diff = ps_values[ind] - last_ps_values[ind];
    if (diff < 0.001) {
      diff = 0;
    }
    dist_values[ind] = diff*encoder_unit;
    last_ps_values[ind] = ps_values[ind];
  }

  float v = (dist_values[0]+dist_values[1])/2.0;
  float w = (dist_values[0]-dist_values[1])/distance_between_wheels;   

  float dt = timestep / 1000.0;
  robot_pose[2] += w * dt;
  float vx = v * cos(robot_pose[2]);
  float vy = v * sin(robot_pose[2]);

  robot_pose[0] += vx * dt;
  robot_pose[1] += vy * dt;

  Serial.print("robot_pose: ");
  Serial.print(robot_pose[0]);
  Serial.print(" ");
  Serial.println(robot_pose[1]);

  digitalWrite(LEFT_MOTOR_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN, HIGH);

  delay(timestep);
}
