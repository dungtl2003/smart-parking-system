#include <SPS_Gate.h>
#include <SPS_Display.h>
#include <SPS_Infrared_Sensor.h>

#define OPEN 1
#define CLOSE 0

#define IR_CAR_1 2
#define IR_CAR_2 3
#define IR_CAR_3 4
#define IR_CAR_4 5
#define IR_CAR_5 6
#define IR_CAR_6 7
#define IR_ENTRY_FRONT 8
#define IR_ENTRY_BACK 9
#define IR_EXIT_FRONT 10
#define IR_EXIT_BACK 11

#define SERVO_ENTER_PIN 12
#define SERVO_EXIT_PIN 13
#define SERVO_DELAY_MS 0

#define LCD_ADDR 0x27
#define LCD_FPS 60

#define TOTAL_SLOTS 6

SPS_InfraredSensor infraredSensor(IR_CAR_1, IR_CAR_2, IR_CAR_3, IR_CAR_4, IR_CAR_5, IR_CAR_6, IR_ENTRY_FRONT, IR_ENTRY_BACK, IR_EXIT_FRONT, IR_EXIT_BACK);
SPS_Display display(LCD_ADDR, LCD_FPS);
SPS_Gate entryGate(SERVO_ENTER_PIN, SERVO_DELAY_MS);
SPS_Gate exitGate(SERVO_EXIT_PIN, SERVO_DELAY_MS);

bool hasSlot;
int slotStates[TOTAL_SLOTS];

bool isEntryFrontSensorDetected;
bool isEntryBackSensorDetected;
bool isExitFrontSensorDetected;
bool isExitBackSensorDetected;

void setup() {
  hasSlot = true;

  isEntryFrontSensorDetected = false;
  isEntryBackSensorDetected = false;
  isExitFrontSensorDetected = false;
  isExitBackSensorDetected = false;

  infraredSensor.init();
  display.init();
  entryGate.init();
  exitGate.init();
}

void loop() {
  readSensor();
  render();

  if (getEntryGateState() == OPEN) {
    entryGate.open();
  } else {
    entryGate.close();
  }

  if (getExitGateState() == OPEN) {
    exitGate.open();
  } else {
    exitGate.close();
  }
}

int getEntryGateState() {
  if (hasSlot && (isEntryFrontSensorDetected || isEntryBackSensorDetected)) {
    return OPEN;
  }

  return CLOSE;
}

int getExitGateState() {
  if (isExitFrontSensorDetected || isExitBackSensorDetected) {
    return OPEN;
  }

  return CLOSE;
}

void readSensor() {
  int slotsLeft = TOTAL_SLOTS;

  for (int i = 0; i < 6; i++) {
    slotStates[i] = infraredSensor.isParkingSensorDetected(i) ? 1 : 0;
    slotsLeft = slotsLeft - slotStates[i];
  }

  hasSlot = slotsLeft > 0;

  isEntryFrontSensorDetected = infraredSensor.isEntryFrontSensorDetected();
  isEntryBackSensorDetected = infraredSensor.isEntryBackSensorDetected();
  isExitFrontSensorDetected = infraredSensor.isExitFrontSensorDetected();
  isExitBackSensorDetected = infraredSensor.isExitBackSensorDetected();
}

void render() {
  display.render(slotStates[0], slotStates[1], slotStates[2], slotStates[3], slotStates[4], slotStates[5]);
}
