/*

Final Arduino controller code for Applied Robotics

Allows for the Yun to listen to the computer and then take the
desired actions based upon that input

 */

// Needed libraries 
#include <Console.h> // WiFi Connection
#include <Wire.h> // Serial Communication
#include <Adafruit_MotorShield.h> // Using the motor shields

// Making the motor shield objects
Adafruit_MotorShield DC_Shield = Adafruit_MotorShield(0x61);
Adafruit_MotorShield Stepper_Shield = Adafruit_MotorShield(0x60);

// What speed we want the vehicle to go - user can change this
int drive_speed = 120;
int current_speed = drive_speed;

// Constants for stepper step size and speed change
int step_size = 4;
int speed_change = 7;

// Mode control for easier driving
bool normal_mode = true;

// Getting the 4 DC motors - named by location
Adafruit_DCMotor *dcMotorFR = DC_Shield.getMotor(1);
Adafruit_DCMotor *dcMotorFL = DC_Shield.getMotor(2);
Adafruit_DCMotor *dcMotorBR = DC_Shield.getMotor(3);
Adafruit_DCMotor *dcMotorBL = DC_Shield.getMotor(4);

// Getting the stepper motor
Adafruit_StepperMotor *stepper = Stepper_Shield.getStepper(200,1);

// Function to move the vehicle forward
void moveForward(int speed) {
	dcMotorFR->run(FORWARD);
    dcMotorFL->run(FORWARD);
    dcMotorBR->run(FORWARD);
    dcMotorBL->run(FORWARD);
        
    dcMotorFR->setSpeed(speed);  
    dcMotorFL->setSpeed(speed);
    dcMotorBR->setSpeed(speed);
    dcMotorBL->setSpeed(speed);

    current_speed = drive_speed;
}

// Function to move the vehicle backward
void moveBackward(int speed) {
	dcMotorFR->run(BACKWARD);
    dcMotorFL->run(BACKWARD);
    dcMotorBR->run(BACKWARD);
    dcMotorBL->run(BACKWARD);
        
    dcMotorFR->setSpeed(speed);  
    dcMotorFL->setSpeed(speed);
    dcMotorBR->setSpeed(speed);
    dcMotorBL->setSpeed(speed);

    current_speed = drive_speed;
}

// Function to turn left
void turnLeft(int speed) {
	dcMotorFR->run(FORWARD);
    dcMotorFL->run(BACKWARD);
    dcMotorBR->run(FORWARD);
    dcMotorBL->run(BACKWARD);
        
    dcMotorFR->setSpeed(drive_speed);  
    dcMotorFL->setSpeed(drive_speed);
    dcMotorBR->setSpeed(drive_speed);
    dcMotorBL->setSpeed(drive_speed);

    current_speed = drive_speed;
}

// Function to turn right
void turnRight(int speed) {
	dcMotorFR->run(BACKWARD);
    dcMotorFL->run(FORWARD);
    dcMotorBR->run(BACKWARD);
    dcMotorBL->run(FORWARD);
        
    dcMotorFR->setSpeed(drive_speed);  
    dcMotorFL->setSpeed(drive_speed);
    dcMotorBR->setSpeed(drive_speed);
    dcMotorBL->setSpeed(drive_speed);

    current_speed = drive_speed;
}

// Function to stop the vehicle
void stopVehicle() {
	dcMotorFR->run(RELEASE);
    dcMotorFL->run(RELEASE);
    dcMotorBR->run(RELEASE);
    dcMotorBL->run(RELEASE);
}

void changeSpeed(int speed) {
	  //Console.println(speed);
    if (speed < 0) {
      speed = 0;
    }
	  dcMotorFR->setSpeed(speed);  
    dcMotorFL->setSpeed(speed);
    dcMotorBR->setSpeed(speed);
    dcMotorBL->setSpeed(speed);
}

// Setup code
void setup() {
	// Begining all shield and communication links
  	DC_Shield.begin();
  	Stepper_Shield.begin();
  	Bridge.begin();
  	Console.begin();

  	// Wait for Console port to connect
  	while (!Console);

  	Console.println("I am a robot. I have been connected.");

  	// Setting stepper speed
  	stepper->setSpeed(10);
}

// Loop code - runs over and over on arduino
// Purpose here is to monitor the communication
// and provide the proper commands to the robot
void loop() { 
  
  	// If there is something avaliable
  	if (Console.available() > 0) {
    	
    	char c = Console.read(); // read the next char received
        
        if (c == 'f' || c == 'F') {
          	if (normal_mode) {
                moveForward(drive_speed);
            }

            else {
                moveBackward(drive_speed);
            }
        }
        
        else if (c == 'b' || c == 'B') {
          	if (normal_mode) {
              moveBackward(drive_speed);
            }

            else {
              moveForward(drive_speed);
            }
        } 
       	
       	else if (c == 'l' || c == 'L') {
          	if (normal_mode) {
              turnLeft(drive_speed);
            }

            else {
              turnLeft(drive_speed);
            }
        } 
        
        else if (c == 'r' || c == 'R') {
          	if (normal_mode) {
              turnRight(drive_speed);
            }

            else {
              turnRight(drive_speed);
            }
        } 
   
   		else if (c == 's' || c == 'S') {
    		stopVehicle();
  		} 

  		else if (c == 'w' || c == 'W') {
    		drive_speed = drive_speed + speed_change;
    		Console.println(drive_speed);
  		} 

  		else if (c == 'x' || c == 'X') {
    		drive_speed = drive_speed - speed_change;
    		Console.println(drive_speed);
  		} 

  		else if (c == 'q' || c == 'Q') {
    		Console.println("Stepping Forward");
    		stepper->step(step_size,FORWARD,SINGLE);  
  		} 
  		else if (c == 'z' || c == 'Z') {
    		Console.println("Stepping Backward");
    		stepper->step(step_size,BACKWARD,SINGLE);
  		}

      else if (c == 'm' || c == 'M') {
        normal_mode = !normal_mode;
        Console.println(normal_mode);
      }
  	}

  	else {
      if (current_speed > 0) {
  		  current_speed = current_speed - speed_change;
  		  changeSpeed(current_speed);
      }
  	}
   delay(10);
}
