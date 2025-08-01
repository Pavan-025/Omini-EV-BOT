#define BLYNK_TEMPLATE_ID "TMPL3-6ZOJMDP"
#define BLYNK_TEMPLATE_NAME "EV BOT"
#define BLYNK_AUTH_TOKEN "_DKfiu_a10BEKOfSrJ9xTtynnPLAc-zg"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Motor Pin Definitions using your specified GPIO pins
#define IN1 D1   // GPIO5 for right motor IN1
#define IN2 D2   // GPIO4 for right motor IN2
#define IN3 D3   // GPIO0 for left motor IN1
#define IN4 D4   // GPIO2 for left motor IN2
#define ENA D5   // GPIO14 for right motor PWM (Enable)
#define ENB D6   // GPIO12 for left motor PWM (Enable)

#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1
#define MAX_MOTOR_SPEED 1023

char ssid[] = "Realme 8 5G";
char pass[] = "0987654321";

struct MOTOR_PINS {
  int pinIN1;
  int pinIN2;
  int pinEn;
};

MOTOR_PINS motorPins[] = {
  {IN1, IN2, ENA},  // RIGHT motor
  {IN3, IN4, ENB}   // LEFT motor
};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 2; i++) {
    pinMode(motorPins[i].pinIN1, OUTPUT);
    pinMode(motorPins[i].pinIN2, OUTPUT);
    pinMode(motorPins[i].pinEn, OUTPUT);
    rotateMotor(i, 0);  // Stop initially
  }

  WiFi.begin(ssid, pass);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// 🔄 Motor control function
void rotateMotor(int motorIndex, int speed) {
  if (speed > 0) {
    digitalWrite(motorPins[motorIndex].pinIN1, HIGH);
    digitalWrite(motorPins[motorIndex].pinIN2, LOW);
  } else if (speed < 0) {
    digitalWrite(motorPins[motorIndex].pinIN1, LOW);
    digitalWrite(motorPins[motorIndex].pinIN2, HIGH);
  } else {
    digitalWrite(motorPins[motorIndex].pinIN1, LOW);
    digitalWrite(motorPins[motorIndex].pinIN2, LOW);
  }
  analogWrite(motorPins[motorIndex].pinEn, abs(speed));
}

// 🔘 Blynk Virtual Button: FORWARD
BLYNK_WRITE(V0) {
  int value = param.asInt();
  if (value == 1) {
    rotateMotor(RIGHT_MOTOR, MAX_MOTOR_SPEED);
    rotateMotor(LEFT_MOTOR, MAX_MOTOR_SPEED);
  } else {
    rotateMotor(RIGHT_MOTOR, 0);
    rotateMotor(LEFT_MOTOR, 0);
  }
}

// 🔘 Blynk Virtual Button: BACKWARD
BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    rotateMotor(RIGHT_MOTOR, -MAX_MOTOR_SPEED);
    rotateMotor(LEFT_MOTOR, -MAX_MOTOR_SPEED);
  } else {
    rotateMotor(RIGHT_MOTOR, 0);
    rotateMotor(LEFT_MOTOR, 0);
  }
}

// 🔘 Blynk Virtual Button: LEFT
BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value == 1) {
    rotateMotor(RIGHT_MOTOR, MAX_MOTOR_SPEED);
    rotateMotor(LEFT_MOTOR, -MAX_MOTOR_SPEED);
  } else {
    rotateMotor(RIGHT_MOTOR, 0);
    rotateMotor(LEFT_MOTOR, 0);
  }
}

// 🔘 Blynk Virtual Button: RIGHT
BLYNK_WRITE(V3) {
  int value = param.asInt();
  if (value == 1) {
    rotateMotor(RIGHT_MOTOR, -MAX_MOTOR_SPEED);
    rotateMotor(LEFT_MOTOR, MAX_MOTOR_SPEED);
  } else {
    rotateMotor(RIGHT_MOTOR, 0);
    rotateMotor(LEFT_MOTOR, 0);
  }
}

void loop() {
  Blynk.run();
}
