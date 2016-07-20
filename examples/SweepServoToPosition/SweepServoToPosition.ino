/*
 * Turns the Servo-motor shaft to the position set by the user through a potentiometer connected to the analog
 * input A2 in the range -64 to 64 steps (-2 to +2 tuns with a 32 CPR encoder).
 *
 * Hardware:
 * --------
 * Modified [Arduino Motor Shield](https://www.arduino.cc/en/Main/ArduinoMotorShieldR3). Male pins have been cut off
 * and pin D3 and D5 have been bridged on the top side of the shield. Pins D2 and D3 have been left free in Arduino
 * to connect the encoder feedback. The outputs of channels A and B have been connected in parallel to provide 4 Amps.
 *
 * A 12V geared DC motor from a battery drill. Output speed aprox 600rpm
 *
 * A DIY Quad encoder made with with two [Pololu QTR-1RC Reflectance sensors](https://www.pololu.com/product/2459) that
 * provides 32CPR.
 *
 * Connections:
 * ------------
 * Arduino motor shield connections:
 * 
 * Function         | Channel A   | Channel B |
 *---------------------------------------------
 * Direcion         | D12 	  | D13       |
 *---------------------------------------------
 * PWM	            | D5 (brigded | D11       |
 *                  | to D3)      |           |
 ----------------------------------------------
 * Brake            | D9          | D8        |
 *---------------------------------------------
 * Current sensing  | A0          | A1        |
 ---------------------------------------------- 
 *
 * When the Direction pins are HIGH the motor turns CCW and
 * CW when LOW.
 *
 * The potntiometer is connected as a tension divider between 0 and 5V. Its
 * central pin (output) to the A2 Arduino input.
 * 
 * Front view of the encoders location
 *
 *       B
 *      ***
 *     *   * A
 *      ***
 * CCW <----> CW
 *
 *  Encoder A -> D2 (Arduino, not motor shield)
 *  Encoder B -> D3 (Arduino, not motor shield)
 *
 *  Activation sequence
 *                 ______        ______
 *  Encoder B  ___|      |______|      |______
 *                    ______        ______
 *  Encoder A  ______|      |______|      |______
 *             (+) CW-->               <--CCW (-)                    
 *
 * Author: Javier Casado July 2016
 * License: CC SHA BY
 */
#include <Encoder.h>
#include <PID_v1.h>
#include <DCMotorServo.h>

#define pin_dcmoto_dirA 12
#define pin_dcmoto_dirB 13
#define pin_dcmoto_pwm_outA 5
#define pin_dcmoto_pwm_outB 11
#define pin_dcmoto_encodeA 2
#define pin_dcmoto_encodeB 3


DCMotorServo servo = DCMotorServo(pin_dcmoto_dirA, pin_dcmoto_dirB, pin_dcmoto_pwm_outA,pin_dcmoto_pwm_outB, pin_dcmoto_encodeA, pin_dcmoto_encodeB);

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
