/*
 * Turns the Servo-motor shaft to the position set by the user through the serial port.
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
 *
 * When the Direction pins are HIGH the motor turns CCW and
 * CW when LOW.
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

void setup() {

  //Tune the servo feedback
  //Determined by trial and error
  //servo.myPID->SetTunings(0.1,0.15,0.05);
  servo.myPID->SetTunings(0.45,0,0.1);
  servo.myPID->SetSampleTime(50);  
  servo.setPWMSkip(80);
  servo.setAccuracy(8);
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

