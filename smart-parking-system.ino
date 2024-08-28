#include <SPS_GateControl.h>
#include <Servo.h>
#include <SPS_Display.h>
#include <SPS_Infrared_Sensor.h>
#include <SoftwareSerial.h>

#define ir_enter 4
#define ir_exit 11
#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

int slot = 6;
int* slotState;
int enterState;
int exitState;
SPS_InfraredSensor infraredSensor(ir_car1, ir_car2, ir_car3, ir_car4, ir_car5, ir_car6, ir_enter, ir_exit);
SPS_Display display(0x27, 45);  
SPS_GateControl gate1();
SPS_GateControl gate2();

Servo servoLeft;
Servo servoRight;

void setup() {
    Serial.begin(9600);
    infraredSensor.init();
    display.init();

    servoLeft.attach(3);
    servoLeft.write(35);
    servoRight.attach(12);
    servoRight.write(90);
}

void loop() {
    Read_Sensor();

    display.render(slotState[0], slotState[1], slotState[2], slotState[3], slotState[4], slotState[5])
    

    // up barrier : TODO
    if (digitalRead(ir_enter1) == 0 && digitalRead(ir_enter2) == 1) {
      if (slot > 0) {
        Serial.println(" Up ");
        servoLeft.write(35); 
      } else {
        lcd.setCursor(0, 0);
        lcd.print(" Sorry Parking Full ");  
        delay(1500);
      }   
    }

    if (digitalRead(ir_back1) == 0 && digitalRead(ir_back2) == 1) {
      servoRight.write(180); 
    }


    // down barrier : TODO
    if (digitalRead(ir_enter1) == 1 && digitalRead(ir_enter2) == 1) {
      Serial.println(" Down ");
      servoLeft.write(135);
    }

    if (digitalRead(ir_back1) == 1 && digitalRead(ir_enter2) == 1) {
      servoRight.write(90);
    }

    delay(1000);
}

void Read_Sensor() {
    slot = 6;

    slotState = infraredSensor.getSlotState();
    enterState = infraredSensor.getEnterState();
    exitState = infraredSensor.getExitState();
    
    for(int i=0; i<6; i++){
      slot = slot - slotState[i];
    }
}