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

const int max_speed = 255;
const int min_speed = 0;

// Constants for stepper step size and speed change
int step_size = 3;
int speed_change = 12;

// Mode control for easier driving
bool normal_mode = true;

// Turn boost
const int boost = 40;

// Getting the 4 DC motors - named by location
Adafruit_DCMotor *dcMotorFR = DC_Shield.getMotor(1);
Adafruit_DCMotor *dcMotorFL = DC_Shield.getMotor(2);
Adafruit_DCMotor *dcMotorBR = DC_Shield.getMotor(3);
Adafruit_DCMotor *dcMotorBL = DC_Shield.getMotor(4);

// Getting the stepper motor
Adafruit_StepperMotor *stepper = Stepper_Shield.getStepper(200,1);

int speedCheck(int speed) {
    if (speed > max_speed) {
      speed = max_speed;
    }

    else if (speed < min_speed) {
      speed = min_speed;
    }

    return speed;

}

// Function to move the vehicle forward
void moveForward() {
	  dcMotorFR->run(FORWARD);
    dcMotorFL->run(FORWARD);
    dcMotorBR->run(FORWARD);
    dcMotorBL->run(FORWARD);
    
    current_speed = drive_speed;

    dcMotorFR->setSpeed(current_speed);  
    dcMotorFL->setSpeed(current_speed);
    dcMotorBR->setSpeed(current_speed);
    dcMotorBL->setSpeed(current_speed);

    
}

// Function to move the vehicle backward
void moveBackward() {
	  dcMotorFR->run(BACKWARD);
    dcMotorFL->run(BACKWARD);
    dcMotorBR->run(BACKWARD);
    dcMotorBL->run(BACKWARD);
    
    current_speed = drive_speed;

    dcMotorFR->setSpeed(current_speed);  
    dcMotorFL->setSpeed(current_speed);
    dcMotorBR->setSpeed(current_speed);
    dcMotorBL->setSpeed(current_speed);

    
}

// Function to turn left
void turnLeft() {
	dcMotorFR->run(FORWARD);
    dcMotorFL->run(BACKWARD);
    dcMotorBR->run(FORWARD);
    dcMotorBL->run(BACKWARD);
    
    current_speed = drive_speed;

    dcMotorFR->setSpeed(speedCheck(current_speed + boost));  
    dcMotorFL->setSpeed(speedCheck(current_speed + boost));
    dcMotorBR->setSpeed(speedCheck(current_speed + boost));
    dcMotorBL->setSpeed(speedCheck(current_speed + boost));

    
}

// Function to turn right
void turnRight() {
	  dcMotorFR->run(BACKWARD);
    dcMotorFL->run(FORWARD);
    dcMotorBR->run(BACKWARD);
    dcMotorBL->run(FORWARD);
    
    current_speed = drive_speed;

    dcMotorFR->setSpeed(speedCheck(current_speed + boost));  
    dcMotorFL->setSpeed(speedCheck(current_speed + boost));
    dcMotorBR->setSpeed(speedCheck(current_speed + boost));
    dcMotorBL->setSpeed(speedCheck(current_speed + boost));

    
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
	  dcMotorFR->setSpeed(speed);  
    dcMotorFL->setSpeed(speed);
    dcMotorBR->setSpeed(speed);
    dcMotorBL->setSpeed(speed);
}

void pulseStepper() {

  stepper->step(1,BACKWARD,MICROSTEP);
  stepper->step(1,FORWARD,MICROSTEP);
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
                moveForward();
            }

            else {
                moveBackward();
            }
        }
        
        else if (c == 'b' || c == 'B') {
          	if (normal_mode) {
              moveBackward();
            }

            else {
              moveForward();
            }
        } 
       	
       	else if (c == 'l' || c == 'L') {
          	if (normal_mode) {
              turnLeft();
            }

            else {
              turnLeft();
            }
        } 
        
        else if (c == 'r' || c == 'R') {
          	if (normal_mode) {
              turnRight();
            }

            else {
              turnRight();
            }
        } 
   
   		else if (c == 's' || c == 'S') {
    		stopVehicle();
  		} 

  		else if (c == 'w' || c == 'W') {
    		drive_speed = speedCheck(drive_speed + speed_change);
    		Console.println(drive_speed);
  		} 

  		else if (c == 'x' || c == 'X') {
    		drive_speed = speedCheck(drive_speed - speed_change);
    		Console.println(drive_speed);
  		} 

  		else if (c == 'q' || c == 'Q') {
    		Console.println("Stepping Forward");
    		stepper->step(step_size,FORWARD,MICROSTEP);  
  		} 
  		else if (c == 'z' || c == 'Z') {
    		Console.println("Stepping Backward");
    		stepper->step(step_size,BACKWARD,MICROSTEP);
  		}

      else if (c == 'm' || c == 'M') {
        normal_mode = !normal_mode;
        Console.println(normal_mode);
      }
  	}

  	else {
      if (current_speed > 0) {
  		  current_speed = speedCheck(current_speed - speed_change);
  		  changeSpeed(current_speed);
      }

      //pulseStepper();
      
  	}
   delay(10);
}
