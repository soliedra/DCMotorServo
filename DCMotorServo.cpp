#include <DCMotorServo.h>

DCMotorServo::DCMotorServo(MotorDriver * driver, Encoder * encoder)
{
	_driver = driver;
	_position = encoder;
	_PWM_output = 0;  
	_pwm_skip = 50;
	_position_accuracy = 30;
  
	_PID_input = _position->read();
	_PID_output = 0;
	_PID_setpoint = _PID_input;
	myPID = new PID(&_PID_input, &_PID_output, &_PID_setpoint,.1,.2,.1, DIRECT);

	myPID->SetSampleTime(50);
	myPID->SetOutputLimits(_pwm_skip-255, 255-_pwm_skip);

	//turn the PID on
	myPID->SetMode(AUTOMATIC);
}

void DCMotorServo::setCurrentPosition(int new_position)
{
  _position->write(new_position);
  _PID_input = _position->read();
}

void DCMotorServo::setAccuracy(unsigned int range)
{
  _position_accuracy = range;
}

bool DCMotorServo::setPWMSkip(uint8_t range)
{
  if ( 0 <= range && range < 255) {
    _pwm_skip = range;
    return 1;
  }
  else
    return 0;
}

//void DCMotorServo::SetPIDTunings(double Kp, double Ki, double Kd)
//{
//	myPID->SetTunings(Kp, Ki, Kd);
//}

bool DCMotorServo::finished()
{
  if (abs(_PID_setpoint - _PID_input) < _position_accuracy && _PWM_output == 0)
    return 1;
  return 0;
 
}

void DCMotorServo::move(int new_rela_position)
{
  //use _PID_setpoint so that we don't introduce errors of _position_accuracy
  _PID_setpoint = _PID_setpoint + new_rela_position;
}

void DCMotorServo::moveTo(int new_position)
{
  _PID_setpoint = new_position;
}

int DCMotorServo::getRequestedPosition()
{
  return _PID_setpoint;
}

int DCMotorServo::getActualPosition()
{
  return _position->read();
}

void DCMotorServo::run() {
  _PID_input = _position->read();
  myPID->Compute();
  
  //_PWM_output can be positive or negative now
  if(_PID_output > 0) {
    _PWM_output = _PID_output + _pwm_skip;
  } 
  else 
  {
	  _PWM_output = _PID_output - _pwm_skip;
  }
 
  if (abs(_PID_setpoint - _PID_input) < _position_accuracy)
  {
    myPID->SetMode(MANUAL);
    _PID_output = 0;
    _PWM_output = 0;
  }
  else
  {
    myPID->SetMode(AUTOMATIC);
  }

  _driver->writePWM(_PWM_output);
}

void DCMotorServo::stop() {
  myPID->SetMode(MANUAL);
  _PID_output = 0;
  _PWM_output = 0;
  _driver->writePWM(_PWM_output);
}

