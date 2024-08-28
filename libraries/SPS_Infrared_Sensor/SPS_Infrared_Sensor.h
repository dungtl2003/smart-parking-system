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
		* @param   irEnter1    digital port in arduino uno that used by entrance gate in the front
		* @param   irEnter2    digital port in arduino uno that used by entrance gate in the back
		* @param   irExit1     digital port in arduino uno that used by exit gate in the back
		* @param   irExit2     digital port in arduino uno that used by exit gate in the front
		*/
		SPS_InfraredSensor(int irCar1, int irCar2, int irCar3, int irCar4, int irCar5, int irCar6, int irEnter1, int irEnter2, int irExit1, int irExit2);
		
		/**
		* Setup all infrared port connection. Must be called before using other functions
		*/
		void init();
		
		/**
		* Get all parking slot sensor's state
		*/
		int* getSlotState();

		/**
		* Get all enter sensor's state
		*/
		int* getEnterState();

		/**
		* Get all exit sensor's state
		*/
		int* getExitState();
    private:
		int parkingSensors[6];
		int enterSensors[2];
		int exitSensors[2];
		int slotState[6];
		int enterState[2];
		int exitState[2];
};

#endif