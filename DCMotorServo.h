/* Encoder Library, for measuring quadrature encoded signals
 * http://www.pjrc.com/teensy/td_libs_Encoder.html*/
#include <Encoder.h>
#include <PID_v1.h>

/*
 * This library uses PID and Encoder feedback to control a DC motor. It's modeled a little bit after the AccelStepper library.

 * The two channels (A and B) of the Arduino motor shield have been connected
 * in parallel to be able to drive up to 4 Amps to the DC motor.
 *
 *
 * DC motor driver connections:
 * 
 * Function         | Channel A   | Channel B |
 *---------------------------------------------
 * Direcion         | D12 	  | D13       |
 *---------------------------------------------
 * PWM	            | D5	  | D11       |
 *---------------------------------------------
 * Brake            | D9      | D8        |
 *---------------------------------------------
 * Current sensing  | A0      | A1        |
 ----------------------------------------------
 *
 * When the Direction pins are HIGH the motor turns CCW and
 * CW when LOW.
 * 
 * NOTICE: In an Arduino motor shield digital pin 3 is used to carry 
 * the Channel A PWM signal. As long  as that same pin is used by the encoder B input
 * pin (external interrupt), channel A PWM has been moved to digital PIN 5.
 * In my case the Digital male pins 2 and 3 have been cut off from the motor
 * Shield, and the pin 3 has been brigded to the arduino pin 5 on the top side
 * of the shield with a piece of wire.
 * 
 * 
 * Hardware
 * --------
 * Modified [Arduino Motor Shield](https://www.arduino.cc/en/Main/ArduinoMotorShieldR3) as mentioned above.
 * Arduino UNO R3
 * A 12V geared DC motor from a battery drill. Output speed aprox 600rpm
 * A DIY Quad encoder made with with two [Pololu QTR-1RC Reflectance sensors](https://www.pololu.com/product/2459) that
 * provides 8CPR.
 *
 * Front view of the encoders location
 *
 *       A
 *      ***
 *     *   * B
 *      ***
 * CCW <----> CW
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
 *             <--CCW  (-)                    (+)   CW-->
 *
 * 
 * Pins
 * ----
 * The outputs of the Driver channels A and B have been connected in parallel to reach a max current of 4 Amps
 * Only the Driver PWM and direction pins have been used. 
 * The Quad encoder channel A (North side of the motor shaft, front view) connected to pin D2 (external interrupt)
 * The Quad encoder channel B (East side of the motor shaft, front view) connected to pin D3 (external interrupt) 
 * 
 * Modified by Javier Casado July 2016
 */


class DCMotorServo {
public:
  DCMotorServo(uint8_t pin_dir_A = 12, uint8_t pin_dir_B = 13, uint8_t pin_pwm_output_A = 5,uint8_t pin_pwm_output_B = 11, uint8_t pin_encode_1 = 2, uint8_t pin_encode_2 = 3);
  PID * myPID;
  void run();
  void stop();
  void move(int new_rela_position);
  void moveTo(int new_position);
  int getRequestedPosition();
  int getActualPosition();
  bool finished();
  bool setPWMSkip(uint8_t);
  void setAccuracy(unsigned int);
  void setCurrentPosition(int);
private:
  uint8_t _pin_PWM_output_A, _pin_PWM_output_B, _pin_dir_A, _pin_dir_B;
  double _PID_setpoint, _PID_input, _PID_output;
  uint8_t _PWM_output;
  
  Encoder * _position;
  uint8_t _pwm_skip;            //The range of PWM to skip (for me, I set it to 50 because duty-cycles under 50/255 are not enough to surpass motor and gearing frictions)
  uint8_t _position_accuracy;   //Set to the highest tolerable inaccuracy (units are encoder counts)
  void _pick_direction();
};
