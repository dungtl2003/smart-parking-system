#include "SPS_Infrared_Sensor.h"
#include <Arduino.h>

SPS_InfraredSensor::SPS_InfraredSensor(int irCar1, int irCar2, int irCar3, int irCar4, int irCar5, int irCar6, int irEnter1, int irEnter2, int irExit1, int irExit2) {
    parkingSensors[0] = irCar1;
    parkingSensors[1] = irCar2;
    parkingSensors[2] = irCar3;
    parkingSensors[3] = irCar4;
    parkingSensors[4] = irCar5;
    parkingSensors[5] = irCar6;
    enterSensors[0] = irEnter1;
	enterSensors[1] = irEnter2;
	exitSensors[0] = irExit1;
	exitSensors[1] = irExit2;	
}

void SPS_InfraredSensor::init(){
    pinMode(parkingSensors[0], INPUT);
    pinMode(parkingSensors[1], INPUT);
    pinMode(parkingSensors[2], INPUT);
    pinMode(parkingSensors[3], INPUT);
    pinMode(parkingSensors[4], INPUT);
    pinMode(parkingSensors[5], INPUT);
    pinMode(enterSensors[0], INPUT);
    pinMode(enterSensors[1], INPUT);
    pinMode(exitSensors[0], INPUT);
    pinMode(exitSensors[1], INPUT);
}

int* SPS_InfraredSensor::getSlotState()  {
    for (int i = 0; i < 6; ++i) {
        slotState[i] = 0;
    }

    if (digitalRead(parkingSensors[0]) == 0) slotState[0] = 1;
    if (digitalRead(parkingSensors[1]) == 0) slotState[1] = 1;
    if (digitalRead(parkingSensors[2]) == 0) slotState[2] = 1;
    if (digitalRead(parkingSensors[3]) == 0) slotState[3] = 1;
    if (digitalRead(parkingSensors[4]) == 0) slotState[4] = 1;
    if (digitalRead(parkingSensors[5]) == 0) slotState[5] = 1;
    return slotState;
}

int* SPS_InfraredSensor::getEnterState() {
    enterState[0] = digitalRead(enterSensors[0]) == 0 ? 1 : 0;
    enterState[1] = digitalRead(enterSensors[1]) == 0 ? 1 : 0;
    return enterState;
}

int* SPS_InfraredSensor::getExitState() {
    exitState[0] = digitalRead(exitSensors[0]) == 0 ? 1 : 0;
    exitState[1] = digitalRead(exitSensors[1]) == 0 ? 1 : 0;
    return exitState;
}