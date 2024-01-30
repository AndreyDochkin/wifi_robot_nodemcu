# Remote Controlled Car with ESP8266 and Blynk

This project allows you to control a remote car using an ESP8266 module and the Blynk app. The car can move forward, backward, left, right, or stop, and you can also control the direction of two servos.

## Components Used

- ESP8266 Wi-Fi module
- Motor driver (PWMA, PWMB, DA, DB)
- Two servo motors (servoX and servoY)
- Blynk IoT platform (for remote control)

## Setup

1. Connect the motor driver and servos to the appropriate pins on the ESP8266.
2. Create a Blynk account, configure the Blynk app, and obtain your Blynk authentication token.
3. Update the Wi-Fi credentials and Blynk token in the code.
4. Upload the code to the ESP8266 module using the Arduino IDE.
5. Run the Blynk app on your smartphone and control the remote car.

## Usage

- Use the Blynk app to control the car's movement (forward, backward, left, right).
- Adjust the direction of the servo motors using Blynk sliders (servoX and servoY).
- The project also supports stopping the car and monitoring the direction.
