#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 200

int enableRightMotor = 6;
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

int enableLeftMotor = 5;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;

// tweak these two values to balance the motors
int rightSpeed = 180;
int leftSpeed = 165;

// tweak this to control how sharply it turns
int turnSpeed = 150;

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  rotateMotor(0, 0);
}

void loop() {
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW) {
    // both on white — go straight
    rotateMotor(rightSpeed, leftSpeed);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
    // right hits black — reverse right wheel, left keeps going
    rotateMotor(-turnSpeed, leftSpeed);
  }
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
    // left hits black — reverse left wheel, right keeps going
    rotateMotor(rightSpeed, -turnSpeed);
  }
  else {
    rotateMotor(0, 0);
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}