#ifndef ServoUnit_h
#define ServoUnit_h

#include "PCA9685.h"

class ServoUnit {
  public:
    ServoUnit();
    ServoUnit(int pinNumber, int startPos, int maxPos, int minPos, PCA9685* driver);
    /**
     * Sets the position of the servo.
     * @param pos The position value to send to the servo (0-180). 
     */
    void setPos(int pos);
    /**
     * Sets the speed of the servo.
     * @param spd The speed value to send to the servo (0-9). A value of zero stops the servo.
     */ 
    void setSpd(int spd);
    /**
     * Sets the target position of the servo (the position the servo should increment towards).
     * @param pos The target position of the servo (0-180).
     */
    void setTargetPos(int pos);
    /**
     * Gets the current position of the servo.
     * @return The position value of the servo (0-180).
     */
    int getPos();
    /**
     * Gets the current speed of the servo.
     * @return The speed of the servo (0-9).
     */
    int getSpd();
    /**
     * Gets the target position of the servo (the position the servo should increment towards).
     * @return The position the servo is incrementing towards (0-180).
     */
    int getTargetPos();
    /**
     * Gets the pin number the current servo is attached to.
     * @return The pin number assigned to the servo.
     */
    int getPin();
  private:
    PCA9685* pwmDriver;
    int _pos;
    int _pin;
    int _max;
    int _min;
    int _spd;
    int _targetPos;
};
    
#endif
