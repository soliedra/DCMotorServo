DCMotorServo
============

An Arduino Library for controlling DC motors with rotary encoders. This library uses PID and Encoder feedback. It is modeled a little bit after the AccelStepper library.

 * Encoder Library, for measuring quadrature encoded signals from http://www.pjrc.com/teensy/td_libs_Encoder.html
 * PID Library, for using encoder feedback to controll the motor from http://playground.arduino.cc/Code/PIDLibrary  also on [GitHub](https://github.com/br3ttb/Arduino-PID-Library)

Circuit
-------
I used a 12V geared motor from a battery drill. As a driver, an [Arduino Motor Shield](https://www.arduino.cc/en/Main/ArduinoMotorShieldR3) dual H brigde driver with the outputs of channels A and B in parallel to reach a max current of 4 Amps (by now I'm not using the brake or current sensing features, only the PWM speed and dir control). And as the Quad Encoder two Pololu QTR1 reflectivity sensors.

### Example circuit connections
<table>
<tr><td>Function</td><td> Channel A </td><td>Channel B</td></tr>
<tr><td>Direction</td><td>D12</td><td>D13</td></tr>
<tr><td>PWM</td><td>D5</td><td>D11</td></tr>
<tr><td>Brake</td><td>D9</td><td>D8</td></tr>
<tr><td>Current sensing </td><td>A0</td><td>A1</td></tr>
</table>

NOTICE Pin D3 moved to D5 !!
---------------------------
In an unmodified Arduino motor shield, digital pin 3 is used to carry the Channel A signal. As long  as that pin is used by the encoder B input pin (external interrupt) channel A PWM has been moved to digital PIN 5 In my case the Digital male pins 0,1,2 and 3 have been cut from the motor Shield, and the pin 3 has been brigded to the arduino pin 5 on the top side of the shield using a short piece if wire.
If you don't want your quad encoder to use interupptions, just use an unmodified Arduino Motor Shield and replace in the code D5 pin by D3. 

Hardware
--------
 * Motor: 12V geared motor from a battery drill
 * Arduino UNO
 * Driver Modified [Arduino Motor Shield](https://www.arduino.cc/en/Main/ArduinoMotorShieldR3)  
 * Quad encoder (DIY type) using [QTR-1RC Reflectance Sensor](https://www.pololu.com/product/959)
  
Pins
----
Pinout for motor control uses:
- 2 PWM enabled pins for speed (the same pwm value will be written to them because channels A and B are connected in parallel). - 2 Output pins for direction (the same value will be written to them because channels A and B are connected in parallel)
- 2 Input and interruption enabled pins, D2 and D3 for the encoder feedback (channels A and B)

ENCODER
--------
Quad encoder with software debouncing section. Provides eight steps per turn
 *
 * Front view of the encoders location
 *
 *       B
 *      ***
 *     *   * A
 *      ***
 *  CW <----> CCW
 * 
 *  Connections:
 *  Encoder A -> ENCODERPINA
 *  Encoder B -> ENCODERPINB
 *
 *  Activation sequence
 *                 ______        ______
 *  Encoder A  ___|      |______|      |______
 *                    ______        ______
 *  Encoder B  ______|      |______|      |______
 *             <--CW  (+)                    (-)   CCW-->
 *
 * Author: Javier Casado, June 2016
 * Released into the public domain

