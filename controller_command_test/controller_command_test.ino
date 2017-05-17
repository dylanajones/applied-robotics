/*
Console Read example for YunShield/Yún

 Read data coming from bridge using the Console.read() function
 and store it in a string.

 To see the Console, pick your Yún's name and IP address in the Port menu
 then open the Port Monitor. You can also see it by opening a terminal window
 and typing:
 ssh root@ yourYunsName.local 'telnet localhost 6571'
 then pressing enter. When prompted for the password, enter it.

 created 13 Jun 2013
 by Angelo Scialabba
 modified 16 June 2013
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/ConsoleRead

 */

#include <Console.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

String name;
Adafruit_MotorShield DC_Shield = Adafruit_MotorShield(0x61);
Adafruit_MotorShield Stepper_Shield = Adafruit_MotorShield(0x60);

uint8_t i_max = 127;

int drive_speed = 120;

Adafruit_DCMotor *dcMotor1 = DC_Shield.getMotor(1);
Adafruit_DCMotor *dcMotor2 = DC_Shield.getMotor(2);
Adafruit_DCMotor *dcMotor3 = DC_Shield.getMotor(3);
Adafruit_DCMotor *dcMotor4 = DC_Shield.getMotor(4);

Adafruit_StepperMotor *stepper = Stepper_Shield.getStepper(200,1);



void setup() {
  DC_Shield.begin();
  Stepper_Shield.begin();
  Bridge.begin();
  Console.begin();

  // Wait for Console port to connect
  while (!Console);

  Console.println("I am a robot. I have been connected.");

  stepper->setSpeed(10);
}

void loop() { 
  
  //Console.println("Starting Loop");
  if (Console.available() > 0) {
    char c = Console.read(); // read the next char received
        if (c == 'f' || c == 'F')
        {
          dcMotor1->run(FORWARD);
          dcMotor2->run(FORWARD);
          dcMotor3->run(FORWARD);
          dcMotor4->run(FORWARD);
        
          dcMotor1->setSpeed(drive_speed);  
          dcMotor2->setSpeed(drive_speed);
          dcMotor3->setSpeed(drive_speed);
          dcMotor4->setSpeed(drive_speed);
        }
        else if (c == 'b' || c == 'B')
        {
          dcMotor1->run(BACKWARD);
          dcMotor2->run(BACKWARD);
          dcMotor3->run(BACKWARD);
          dcMotor4->run(BACKWARD);
        
          dcMotor1->setSpeed(drive_speed);  
          dcMotor2->setSpeed(drive_speed);
          dcMotor3->setSpeed(drive_speed);
          dcMotor4->setSpeed(drive_speed);
        } 
       else if (c == 'l' || c == 'L')
        {

          dcMotor1->run(FORWARD);
          dcMotor2->run(BACKWARD);
          dcMotor3->run(FORWARD);
          dcMotor4->run(BACKWARD);
        
          dcMotor1->setSpeed(drive_speed);  
          dcMotor2->setSpeed(drive_speed);
          dcMotor3->setSpeed(drive_speed);
          dcMotor4->setSpeed(drive_speed);
        } 
        else if (c == 'r' || c == 'R')
        {
          dcMotor1->run(BACKWARD);
          dcMotor2->run(FORWARD);
          dcMotor3->run(BACKWARD);
          dcMotor4->run(FORWARD);
        
          dcMotor1->setSpeed(drive_speed);  
          dcMotor2->setSpeed(drive_speed);
          dcMotor3->setSpeed(drive_speed);
          dcMotor4->setSpeed(drive_speed);
        } 
   else if (c == 's' || c == 'S') {
    dcMotor1->run(RELEASE);
          dcMotor2->run(RELEASE);
          dcMotor3->run(RELEASE);
          dcMotor4->run(RELEASE);

  } else if (c == 'w' || c == 'W'){
    drive_speed = drive_speed + 10;
    Console.println(drive_speed);
  } else if (c == 'x' || c == 'X'){
    drive_speed = drive_speed - 10;
    Console.println(drive_speed);
  } else if (c == 'q' || c == 'Q') {
    Console.println("Stepping Forward");
    stepper->step(5,FORWARD,SINGLE);  
  } else if (c == 'z' || c == 'Z') {
    Console.println("Stepping Backward");
    stepper->step(5,BACKWARD,SINGLE);
  }
  
  }
  

  //delay(10);
}
