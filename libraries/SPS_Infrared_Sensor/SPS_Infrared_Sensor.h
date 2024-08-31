#ifndef SPS_INFRARED_SENSOR_H
#define SPS_INFRARED_SENSOR_H

class SPS_InfraredSensor {
    public:
		/**
		* Manage all the infrared sensor in the
		* @param   irCar1      digital port in arduino uno that used by slot 1
		* @param   irCar2      digital port in arduino uno that used by slot 2
		* @param   irCar3      digital port in arduino uno that used by slot 3
		* @param   irCar4      digital port in arduino uno that used by slot 4
		* @param   irCar5      digital port in arduino uno that used by slot 5
		* @param   irCar6      digital port in arduino uno that used by slot 6
		* @param   irEnter    digital port in arduino uno that used by entrance gate
		* @param   irExit     digital port in arduino uno that used by exit gate
		*/
		SPS_InfraredSensor(int irCar1, int irCar2, int irCar3, int irCar4, int irCar5, int irCar6, int irEnter, int irExit);
		
		/**
		* Setup all infrared port connection. Must be called before using other functions
		*/
		void init();
		
		/**
		* Get all parking slot sensor's state. 1 mean that parking slot is fill and vice versa
		*/
		int* getSlotStates();

		/**
		* Get enter sensor's state. 1 mean there is an obstacle and vice versa
		*/
		int getEnterSensorState();


		/**
		* Get exit sensor's state. 1 mean there is an obstacle and vice versa
		*/
		int getExitSensorState();

    private:
		int parkingSensors[6];
		int enterSensor;
		int exitSensor;
		int slotStates[6];
		int enterSensorState;
		int exitSensorState;
};

#endif