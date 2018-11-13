#include "PCA9685.h"
#include "ServoUnit.h"
#include <QDebug>

ServoUnit::ServoUnit() {
	_pin = -1;
	_spd = 0;
	_targetPos = 0;
}

ServoUnit::ServoUnit(int pinNumber, int startPos, int maxPos, int minPos, PCA9685* driver) {
  //_servo.attach(pinNumber);
  _pin = pinNumber;
  _max = maxPos;
  _min = minPos;
  pwmDriver = driver;
  _spd = 0;
  _targetPos = startPos;
  _pos = startPos;
  pwmDriver->setPWM(_pin, 0, 100 + (_pos/180 *680) );
}

/**
 * Sets the position of the servo.
 * @param pos The position value to send to the servo (0-180). 
 */
void ServoUnit::setPos(int pos) {
    if(pos >= 0 && pos <= 180){
         _pos = pos;
        qDebug() << "SetPWM[" << _pin << "] :" << (100.0 + (_pos/180.0 *580.0));
        pwmDriver->setPWM(_pin, 0, (int) (100.0 + (_pos/180.0 *580.0)) );
    }
}

/**
 * Sets the speed of the servo.
 * @param spd The speed value to send to the servo (0-9). A value of zero stops the servo.
 */ 
void ServoUnit::setSpd(int spd) {
  _spd = spd;
}

/**
 * Sets the target position of the servo (the position the servo should increment towards).
 * @param pos The target position of the servo (0-180).
 */
void ServoUnit::setTargetPos(int pos) {
	_targetPos = pos;
}

/**
 * Gets the current position of the servo.
 * @return The position value of the servo (0-180).
 */
int ServoUnit::getPos() {
    //return pwmDriver->getPWM(_pin);
    return _pos;
}

/**
 * Gets the current speed of the servo.
 * @return The speed of the servo (0-9).
 */
int ServoUnit::getSpd() {
  return _spd;
}

/**
 * Gets the target position of the servo (the position the servo should increment towards).
 * @return The position the servo is incrementing towards (0-180).
 */
int ServoUnit::getTargetPos() {
  return _targetPos;
}

/**
 * Gets the pin number the current servo is attached to.
 * @return The pin number assigned to the servo.
 */
int ServoUnit::getPin() {
  return _pin;
}


