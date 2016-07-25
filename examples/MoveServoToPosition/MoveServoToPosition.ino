/*
 * Turns the Servo-motor shaft to the position set by the user through the serial port.
 *
 * This library uses PID and Encoder feedback to control a DC motor. It's modeled a little bit after the AccelStepper library.
 *
 * Pololu VNH5019 Driver has been used. 
 *
 *
 * DC motor driver connections
 *-----------------------------
 * 
 * Function         | Pin   
 *----------------------------
 * Direcion A (CW)  | D5	 
 *----------------------------
 * Direcion B (CCW) | D7 	  
 *----------------------------
 * PWM	            | D6	  
 *------------------------------------------
 * Brake (GND)      | D5 and D7 set to LOW  
 *---------------------------------------------
 * Current sensing  | A1      
 ------------------------------
 *
 * 
 * Hardware
 * --------
 * [Pololu VNH5019 Driver](https://www.pololu.com/product/1451) 
 * Arduino UNO R3
 * A 12V geared DC motor from a battery drill. Output speed aprox 600rpm
 * A DIY Quad encoder made with with two [Pololu QTR-1RC Reflectance sensors](https://www.pololu.com/product/2459) that
 * provides 8CPR.
 *
 * Front view of the encoders location
 *
 *        B
 *       ***
 *      *   * A
 *       ***
 * CW(+)<---> CCW (-)
 * 
 *  Connections:
 *  Encoder A -> D2 (Arduino, not motor shield)
 *  Encoder B -> D3 (Arduino, not motor shield)
 *
 *  Activation sequence
 *                 ______        ______
 *  Encoder A  ___|      |______|      |______
 *                    ______        ______
 *  Encoder B  ______|      |______|      |______
 *             CCW-->(-)                   (+) <--CW
 *
 * 
 * Pins
 * ----
 * The Driver pins have been connected as described above. 
 * The Quad encoder channel B (North side of the motor shaft, front view) connected to pin D3 (external interrupt)
 * The Quad encoder channel B (East side of the motor shaft, front view) connected to pin D2 (external interrupt) 
 * 
 * Modified by Javier Casado July 2016
 */
#include <Encoder.h>
#include <PID_v1.h>
#include <DCMotorServo.h>
#include <MotorDriver.h>
#include <VNH5019MotorDriver.h>


#define pin_dcmoto_dirA 5
#define pin_dcmoto_dirB 7
#define pin_dcmoto_pwm  6
#define pin_dcmoto_encodeA 2
#define pin_dcmoto_encodeB 3

VNH5019MotorDriver driver = VNH5019MotorDriver(pin_dcmoto_dirA,pin_dcmoto_dirB,pin_dcmoto_pwm);

Encoder myEncoder = Encoder(pin_dcmoto_encodeB,pin_dcmoto_encodeA);

DCMotorServo servo = DCMotorServo(&driver, &myEncoder);

int targetPosition = 0;

void setup() {

  //Tune the servo feedback
  //Determined by trial and error
  //servo.myPID->SetTunings(0.1,0.15,0.05);
  servo.myPID->SetTunings(0.45,0.0,0.0);
  servo.myPID->SetSampleTime(50);  
  servo.setPWMSkip(50);
  servo.setAccuracy(1);
  //Un-necessary, initializes to 0:
  //servo.setCurrentPosition(0);
  
  Serial.begin(9600);
  Serial.println("Enter target position (+ CW -CCW): "); 
}


void loop() {
  servo.run();

  if (servo.finished()) {
    if(readTargetPosition()) servo.moveTo(targetPosition);
  }
}

/*
 * Returns true when a new position has been read from
 * the Serial port and false otherwise.
 * The value read is stored in the global variable targetPosition.
 */
bool readTargetPosition()
{
	// read speed to be set
	while(Serial.available() > 0) {
		//wait for the incomming data to arrive, avoids partial readings
		delay(10);
		targetPosition = Serial.parseInt();
		//Maybe there's an end of string read as a zero, remove it reading again 
		Serial.parseInt();
		Serial.print("Position: ");
		Serial.println(targetPosition);
                
                // Yes, there was a reading
                return true;
	}
   // By default, no reading
   return false;
}

