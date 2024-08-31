#include "SPS_Infrared_Sensor.h"
#include <Arduino.h>

SPS_InfraredSensor::SPS_InfraredSensor(int irCar1, int irCar2, int irCar3, int irCar4, int irCar5, int irCar6, int irEnter, int irExit) {
    parkingSensors[0] = irCar1;
    parkingSensors[1] = irCar2;
    parkingSensors[2] = irCar3;
    parkingSensors[3] = irCar4;
    parkingSensors[4] = irCar5;
    parkingSensors[5] = irCar6;
    enterSensor = irEnter;
	exitSensor = irExit;	
}

void SPS_InfraredSensor::init(){
    for (int i = 0; i < 6; ++i) {
        pinMode(parkingSensors[i], INPUT);
    }
    pinMode(enterSensor, INPUT);
    pinMode(exitSensor, INPUT);
}

int* SPS_InfraredSensor::getSlotStates()  {
    for (int i = 0; i < 6; ++i) {
        slotStates[i] = 0;
    }

    for (int i = 0; i < 6; ++i) {
        if (digitalRead(parkingSensors[i]) == 0) slotStates[i] = 1;
    }
    return slotStates;
}

int SPS_InfraredSensor::getEnterSensorState() {
    return digitalRead(enterSensor) == 0 ? 1 : 0;
}

int SPS_InfraredSensor::getExitSensorState() {
    return digitalRead(exitSensor) == 0 ? 1 : 0;
}