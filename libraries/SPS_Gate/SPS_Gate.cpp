#include "Arduino.h"
#include "SPS_Gate.h"

SPS_Gate::SPS_Gate(int servoPin, int delayInMs)
    : servoPin(servoPin), delayInMs(delayInMs), position(MIN_DEGREE),
      preMovementTime(-1) {}

SPS_Gate::SPS_Gate(int servoPin, int delayInMs, int maxDegree, int minDegree,
                   int speed)
    : MAX_DEGREE(maxDegree), MIN_DEGREE(minDegree), SPEED(speed) {
  SPS_Gate(servoPin, delayInMs);
}

void SPS_Gate::init() {
  servo.attach(servoPin);
  servo.write(MIN_DEGREE);
}

void SPS_Gate::open() {
  if (position == MAX_DEGREE) {
    return;
  }

  long now = millis();
  if (preMovementTime > -1) {
    long elapsed = now - preMovementTime;
    long timeToWait = delayInMs - elapsed;
    if (timeToWait > 0) {
      return;
    }
  }

  position = position + SPEED > MAX_DEGREE ? MAX_DEGREE : position + SPEED;

  servo.write(position);
  preMovementTime = now;
}

void SPS_Gate::close() {
  if (position == MIN_DEGREE) {
    return;
  }

  long now = millis();
  if (preMovementTime > -1) {
    long elapsed = now - preMovementTime;
    long timeToWait = delayInMs - elapsed;
    if (timeToWait > 0) {
      return;
    }
  }

  position = position - SPEED < MIN_DEGREE ? MIN_DEGREE : position - SPEED;

  servo.write(position);
  preMovementTime = now;
};