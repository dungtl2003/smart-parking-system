#include <SPS_Display.h>
#include <SPS_Infrared_Sensor.h>

#define ir_enter1 2
#define ir_enter2 4
#define ir_back1 11
#define ir_back2 13
#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

SPS_Display display(0x27, 45);
SPS_InfraredSensor infraredSensor(ir_car1, ir_car2, ir_car3, ir_car4, ir_car5, ir_car6, ir_enter1, ir_enter2, ir_back1, ir_back2);

void setup() {
  display.init();
  infraredSensor.init();
}

void loop() {
  // Your loop code here
  display.render(1, 1, 0, 1, 0, 0);
}