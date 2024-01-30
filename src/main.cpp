#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define PWR_LEVEL 850

// Virtual pin definitions for clarity
#define PIN_FORWARD     V1
#define PIN_BACKWARD    V0
#define PIN_LEFT        V2
#define PIN_RIGHT       V3
#define PIN_STOP        99

// Function declarations
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMovement();

// Servo object declaration
Servo servoX;
Servo servoY;

// Network credentials and Blynk authorization
char auth[] = "YourBlynkAuthToken";
char ssid[] = "YourNetworkSSID";
char pass[] = "YourNetworkPassword";

// Motor control pin definitions
const int PWMA = 5; // Right side
const int PWMB = 4; // Left side
const int DA = 0;   // Right reverse
const int DB = 2;   // Left reverse

// Global variables
int x;
int y;
int direction;

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(DA, OUTPUT);
    pinMode(DB, OUTPUT);
    
    servoX.attach(D8);
    servoY.attach(D7);
}

void loop() {
    Blynk.run();
    switch (direction) {
        case PIN_FORWARD:
            moveForward();
            break;
        case PIN_BACKWARD:
            moveBackward();
            break;
        case PIN_LEFT:
            turnLeft();
            break;
        case PIN_RIGHT:
            turnRight();
            break;
        case PIN_STOP:
            stopMovement();
            break;
        default:
            break;
    }
}

BLYNK_WRITE(PIN_FORWARD) {
    direction = param.asInt() ? PIN_FORWARD : PIN_STOP;
}

BLYNK_WRITE(PIN_BACKWARD) {
    direction = param.asInt() ? PIN_BACKWARD : PIN_STOP;
}

BLYNK_WRITE(PIN_LEFT) {
    direction = param.asInt() ? PIN_LEFT : PIN_STOP;
}

BLYNK_WRITE(PIN_RIGHT) {
    direction = param.asInt() ? PIN_RIGHT : PIN_STOP;
}

BLYNK_WRITE(V11) {
    servoX.write(param.asInt());
}

BLYNK_WRITE(V12) {
    servoY.write(param.asInt());
}

// Movement functions
void moveForward() {
    digitalWrite(PWMA, HIGH);
    digitalWrite(DA, LOW);
    digitalWrite(PWMB, HIGH);
    digitalWrite(DB, LOW);
}

void moveBackward() {
    digitalWrite(PWMA, HIGH);
    digitalWrite(DA, HIGH);
    digitalWrite(PWMB, HIGH);
    digitalWrite(DB, HIGH);
}

void turnLeft() {
    analogWrite(PWMA, PWR_LEVEL);
    digitalWrite(DA, HIGH);
    analogWrite(PWMB, PWR_LEVEL);
    digitalWrite(DB, LOW);
}

void turnRight() {
    analogWrite(PWMA, PWR_LEVEL);
    digitalWrite(DA, LOW);
    analogWrite(PWMB, PWR_LEVEL);
    digitalWrite(DB, HIGH);
}

void stopMovement() {
    digitalWrite(PWMA, LOW);
    digitalWrite(DA, LOW);
    digitalWrite(PWMB, LOW);
    digitalWrite(DB, LOW);
}
