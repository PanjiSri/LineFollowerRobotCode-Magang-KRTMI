// Initialize variables
int encoderPinLeftA = 2;
int encoderPinLeftB = 3;
int encoderPinRightA = 4;
int encoderPinRightB = 5;
int previousPositionLeft = 0;
int previousPositionRight = 0;
unsigned long previousTime = 0;

// Define constants
const float wheelRadius = 0.03; // in meters
const int encoderResolution = 50; // pulses per revolution

// Function to calculate velocity from encoder position
float calculateVelocity(int deltaPosition, unsigned long deltaTime) {
  float distance = deltaPosition * wheelRadius * 2 * 3.14159265359 / encoderResolution;
  float velocity = distance / (deltaTime / 1000.0);
  return velocity;
}

void setup() {
  // Configure encoder pins as inputs
  pinMode(encoderPinLeftA, INPUT);
  pinMode(encoderPinLeftB, INPUT);
  pinMode(encoderPinRightA, INPUT);
  pinMode(encoderPinRightB, INPUT);

  // Enable pullup resistors on encoder pins
  digitalWrite(encoderPinLeftA, HIGH);
  digitalWrite(encoderPinLeftB, HIGH);
  digitalWrite(encoderPinRightA, HIGH);
  digitalWrite(encoderPinRightB, HIGH);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read encoder positions
  int positionLeft = digitalRead(encoderPinLeftA) ^ digitalRead(encoderPinLeftB) ^ previousPositionLeft;
  int positionRight = digitalRead(encoderPinRightA) ^ digitalRead(encoderPinRightB) ^ previousPositionRight;

  // Calculate time elapsed since last reading
  unsigned long currentTime = micros();
  unsigned long deltaTime = currentTime - previousTime;

  // Calculate velocity of each wheel
  float velocityLeft = calculateVelocity(positionLeft - previousPositionLeft, deltaTime);
  float velocityRight = calculateVelocity(positionRight - previousPositionRight, deltaTime);

  // Output results to serial monitor
  Serial.print("Left wheel velocity: ");
  Serial.print(velocityLeft);
  Serial.print(" m/s, ");
  Serial.print(velocityLeft * 1000 / 60);
  Serial.println(" RPM");

  Serial.print("Right wheel velocity: ");
  Serial.print(velocityRight);
  Serial.print(" m/s, ");
  Serial.print(velocityRight * 1000 / 60);
  Serial.println(" RPM");

  // Update previous values
  previousPositionLeft = positionLeft;
  previousPositionRight = positionRight;
  previousTime = currentTime;
}
