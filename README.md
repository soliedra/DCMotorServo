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
I've used a Pololu VNH5019 Driver

### Example circuit connections
<table>
<tr><td>Function</td><td>Pin</td></tr>
<tr><td>Direction A (CW) </td><td>D5</td></tr>
<tr><td>Direction B (CCW) </td><td>D7</td></tr>
<tr><td>PMW</td><td>D6</td></tr>
<tr><td>Current sensing</td><td>A1</td></tr>
</table>

When the direction pins are HIGH the motor turns either CCW or CW
When the direction pins are both HIGH the motor brake to Vcc is set.
When the direction pins are both LOW the motor brake to GND is set.
  
Hardware
--------
 * [Pololu VNH5019 Driver](https://www.pololu.com/product/1451).
 * Arduino UNO R3
 * A 12V geared DC motor from a battery drill. Output speed approx 600rpm
 * A DIY Quad encoder made with with two [Pololu QTR-1RC Reflectance sensors](https://www.pololu.com/product/2459) that provides 32CPR in the output shaft of the gearbox.
 
Pins
----
 * Only the direction and PWM pins of the driver are used.
 * The Quad encoder channel A (East side of the motor shaft, front view) connected to pin D2 of the Arduino, not connected through the motor shield but directly to the Arduino board underneath (external interrupt)
 * The Quad encoder channel B (North side of the motor shaft, front view) connected to pin D3 of the Arduino, not connected through the motor shield but directly to the Arduino board underneath (external interrupt)
  
TODO
----
 * Use brake feature and current sensing 
 * implement friendlier tuning method for PID
</pre>
  </body>
</html>
