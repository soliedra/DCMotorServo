/*
 * Turns the Servo-motor shaft to the position set by the user through a potentiometer connected to the analog
 * input A2 in the range -64 to 64 steps (-2 to +2 tuns with a 32 CPR encoder).
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

#define pin_dcmoto_dirA 5
#define pin_dcmoto_dirB 7
#define pin_dcmoto_pwm 	6
#define pin_dcmoto_encodeA 2
#define pin_dcmoto_encodeB 3


DCMotorServo servo = DCMotorServo(pin_dcmoto_dirA, pin_dcmoto_dirB, pin_dcmoto_pwm, pin_dcmoto_encodeA, pin_dcmoto_encodeB);

int targetPosition = 0;
int oldTargetPosition = 0;


void setup() {

  //Tune the servo feedback
  //Determined by trial and error
  //servo.myPID->SetTunings(0.1,0.15,0.05);
  servo.myPID->SetTunings(0.45,0,0.1);
  servo.myPID->SetSampleTime(50);  
  servo.setPWMSkip(80);
  servo.setAccuracy(8);
  
  // we make the current position the initial target position
  targetPosition = map(analogRead(A2),0,1024,-64,64);
  oldTargetPosition = targetPosition;
  servo.setCurrentPosition(targetPosition);
  //Un-necessary, initializes to 0:
  //servo.setCurrentPosition(0);
  
  Serial.begin(9600);
  Serial.println("Set point: 0"); 
}


void loop() {
  servo.run();

  if (servo.finished()) {
    targetPosition = map(analogRead(A2),0,1024,-64,64);
    if(targetPosition != oldTargetPosition) {
      Serial.print("Set point: ");Serial.println(targetPosition); 
      servo.moveTo(targetPosition);
      oldTargetPosition = targetPosition;
    }
  }
}
