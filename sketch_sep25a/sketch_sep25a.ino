#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define PWR_LEVEL 850

#define FORWARD     V1
#define BACKWARD    V0
#define LEFT        V2
#define RIGHT       V3
#define STOP        99

#define LAZER       V10 

void Forward();
void Backward();
void LeftTurn();
void ForwardLeft();
void ForwardRight();
void RightTurn();
void Stop();

Servo servoX;
Servo servoY;

char auth[] = "qqyR56Fz6IGFoeWol6b6pbjis8wbs0h4";
char ssid[] = "TP-Link_39BE";
char pass[] = "02061988";

int LZ_D5 = D5;
int PWMA = 5; //Right side
int PWMB = 4; //Left side
int DA = 0;   //Right reverse
int DB = 2;   //Left reverse
int x;
int y;
int direction;

void setup()
{
     Serial.begin(9600);
     Blynk.begin(auth, ssid, pass);

     pinMode(PWMA, OUTPUT);
     pinMode(PWMB, OUTPUT);
     pinMode(DA, OUTPUT);
     pinMode(DB, OUTPUT);

     pinMode(LZ_D5,OUTPUT);
     
     servoX.attach(D8);
     servoY.attach(D7);
}

void loop()
{
     Blynk.run();
     switch (direction)
     {
     case FORWARD:
          Forward();
          break;
     case BACKWARD:
          Backward();
          break;
     case LEFT:
         // LeftTurn();
         ForwardLeft();
          break;
     case RIGHT:
         // RightTurn();
         ForwardRight();
          break;
     case STOP:
          Stop();
          break;
     default:
          break;
     }
}

//Handling Joystick data
// BLYNK_WRITE(V10)
// {
//      servoX.write (param[0].asInt());
//      servoY.write (param[1].asInt());
// }

BLYNK_WRITE(V11){
    int tmp = 180 - param.asInt();
    
     servoX.write(tmp);
}

BLYNK_WRITE(V12){
   int tmp = 180 - param.asInt();
     servoY.write(tmp);
}

BLYNK_WRITE(LAZER){
  digitalWrite(LZ_D5,param.asInt());  
}


BLYNK_WRITE(BACKWARD)
{
     int a = param.asInt();
     if (a == 0 && direction == BACKWARD)
          direction = STOP;
     if (a == 1)
          direction = BACKWARD;
}

BLYNK_WRITE(FORWARD)
{
     int a = param.asInt();
     if (a == 0 && direction == FORWARD)
          direction = STOP;
     if (a == 1)
          direction = FORWARD;
}

BLYNK_WRITE(LEFT)
{
     int a = param.asInt();
     if (a == 0 && direction == LEFT)
          direction = STOP;
     if (a == 1)
          direction = LEFT;
}

BLYNK_WRITE(RIGHT)
{
     int a = param.asInt();
     if (a == 0 && direction == RIGHT)
          direction = STOP;
     if (a == 1)
          direction = RIGHT;
}


void Forward()
{
     digitalWrite(PWMA, HIGH);
     digitalWrite(DA, LOW);
     digitalWrite(PWMB, HIGH);
     digitalWrite(DB, LOW);
}
void Backward()
{
     digitalWrite(PWMA, HIGH);
     digitalWrite(DA, HIGH);
     digitalWrite(PWMB, HIGH);
     digitalWrite(DB, HIGH);
}
void LeftTurn()
{
     analogWrite(PWMA, PWR_LEVEL);
     digitalWrite(DA, HIGH);
     analogWrite(PWMB, PWR_LEVEL);
     digitalWrite(DB, LOW);
}
void RightTurn()
{
     analogWrite(PWMA, PWR_LEVEL);
     digitalWrite(DA, LOW);
     analogWrite(PWMB, PWR_LEVEL);
     digitalWrite(DB, HIGH);
}
void ForwardLeft()
{
     digitalWrite(PWMA, LOW);
     digitalWrite(DA, LOW);
     analogWrite(PWMB, PWR_LEVEL);
     digitalWrite(DB, LOW);
}
void ForwardRight()
{
     analogWrite(PWMA, PWR_LEVEL);
     digitalWrite(DA, LOW);
     digitalWrite(PWMB, LOW);
     digitalWrite(DB, LOW);
}
void BackwardRight()
{
     digitalWrite(PWMA, HIGH);
     digitalWrite(DA, HIGH);
     digitalWrite(PWMB, LOW);
     digitalWrite(DB, LOW);
}
void BackwardLeft()
{
     digitalWrite(PWMA, LOW);
     digitalWrite(DA, LOW);
     digitalWrite(PWMB, HIGH);
     digitalWrite(DB, HIGH);
}
void Stop()
{
     digitalWrite(PWMA, LOW);
     digitalWrite(DA, LOW);
     digitalWrite(PWMB, LOW);
     digitalWrite(DB, LOW);
}
