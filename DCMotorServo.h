/* Encoder Library, for measuring quadrature encoded signals
 * http://www.pjrc.com/teensy/td_libs_Encoder.html*/
#include <Encoder.h>
#include <PID_v1.h>
#include <MotorDriver.h>
#include <VNH5019MotorDriver.h>

/*
 * This library uses PID and Encoder feedback to control a DC motor. It's modeled a little bit after the AccelStepper library.
 *
 * Pololu VNH5019 Driver has been used. 
 *
 *
 * DC motor driver connections:
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


class DCMotorServo {
public:
  DCMotorServo(MotorDriver * driver, Encoder * encoder);
 
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
  uint8_t _pin_dir_A, _pin_dir_B, _pin_pwm_output, _pin_encode_1, _pin_encode_2;
  double _PID_setpoint, _PID_input, _PID_output;
  uint8_t _PWM_output;
  
  ///VNH5019MotorDriver * _driver;
  MotorDriver * _driver;	
  Encoder * _position;
  uint8_t _pwm_skip;            //The range of PWM to skip (for me, I set it to 50 because duty-cycles under 50/255 are not enough to surpass motor and gearing frictions)
  uint8_t _position_accuracy;   //Set to the highest tolerable inaccuracy (units are encoder counts)
  void _pick_direction();
};
