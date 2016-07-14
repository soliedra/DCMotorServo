<html>
  <head>
    <meta content="text/html; charset=windows-1252" http-equiv="content-type">
    <link rel="alternate stylesheet" type="text/css" href="resource://gre-resources/plaintext.css"
      title="Ajustar líneas largas">
  </head>
  <body>
    <pre>DCMotorServo
============

An Arduino Library for controlling DC motors with rotary encoders. This library uses PID and Encoder feedback. It is modeled a little bit after the AccelStepper library.

 * Encoder Library, for measuring quadrature encoded signals from http://www.pjrc.com/teensy/td_libs_Encoder.html
 * PID Library, for using encoder feedback to controll the motor from http://playground.arduino.cc/Code/PIDLibrary  also on [GitHub](https://github.com/br3ttb/Arduino-PID-Library)

Circuit
-------
I used an Arduino Motor Driver Shield with its two H controllers in parallel to reach a current of 4 Amps. I cut off the male end of the pins pins D0,D1,D2 and D3 so they remain disconnected from the Arduino board underneath, with a short cable bridged the pins D3 and D5 on the top side of the Arduino motor shield. The reason to do this is that pins D2 and D3 in Arduino boards are the external interruption enabled pins that could be needed by the quad encoder.

### Example circuit connections
<table>
<tr><td>Function</td><td>Channel A</td><td>Channel B</td></tr>
<tr><td>Direction</td><td>D12</td><td>D13</td></tr>
<tr><td>PMW</td><td>D5</td><td>D11</td></tr>
<tr><td>Brake</td><td>D9</td><td>D8</td></tr>
<tr><td>Current sensing</td><td>A0</td><td>A1</td></tr>
</table>

When the Direction pins are HIGH the motor turns CCW, and CW when LOW.

  
Hardware
--------
 * Modified [Arduino Motor Shield](https://www.arduino.cc/en/Main/ArduinoMotorShieldR3) as mentioned above.
 * Arduino UNO R3
 * A 12V geared DC motor from a battery drill. Output speed aprox 600rpm
 * A DIY Quad encoder made with with two [Pololu QTR-1RC Reflectance sensors](https://www.pololu.com/product/2459) that
 * provides 32CPR in the output shaft of the gearbox.
 
Pins
----
 * The outputs of the Driver channels A and B have been connected in parallel to reach a max current of 4 Amps
 * Only the Driver PWM and direction pins have been used. 
 * The Quad encoder channel A (North side of the motor shaft, front view) connected to pin D2 of the Arduino, not the motor shield (external interrupt)
 * The Quad encoder channel B (East side of the motor shaft, front view) connected to pin D3 of the Arduino, not the motor shield (external interrupt) 
  
TODO
----
 * Use brake feature and current sensing 
 * implement friendlier tuning method for PID
</pre>
  </body>
</html>
