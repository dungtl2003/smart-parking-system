#include <SPS_Gate.h>
#include <SPS_Display.h>
#include <SPS_Infrared_Sensor.h>
#include <SPS_RFID_Scanner.h>

#define OPEN 1
#define CLOSE 0

#define IR_CAR_1 22
#define IR_CAR_2 23
#define IR_CAR_3 24
#define IR_CAR_4 25
#define IR_CAR_5 26
#define IR_CAR_6 27
#define IR_ENTRY_FRONT 28
#define IR_ENTRY_BACK 29
#define IR_EXIT_FRONT 30
#define IR_EXIT_BACK 31

#define SERVO_ENTER_PIN 9
#define SERVO_EXIT_PIN 8
#define SERVO_DELAY_MS 0

#define RFID_ENTER_SS_PIN 49
#define RFID_ENTER_RST_PIN 48
//#define RFID_EXIT_SS_PIN 53
//#define RFID_EXIT_RST_PIN 46

#define LCD_ADDR 0x27
#define LCD_FPS 45

#define TOTAL_SLOTS 6

SPS_InfraredSensor infraredSensor(IR_CAR_1, IR_CAR_2, IR_CAR_3, IR_CAR_4, IR_CAR_5, IR_CAR_6, IR_ENTRY_FRONT, IR_ENTRY_BACK, IR_EXIT_FRONT, IR_EXIT_BACK);
SPS_Display display(LCD_ADDR, LCD_FPS);
SPS_Gate entryGate(SERVO_ENTER_PIN, SERVO_DELAY_MS);
//SPS_Gate entryGate(SERVO_ENTER_PIN, SERVO_DELAY_MS, 90);
SPS_Gate exitGate(SERVO_EXIT_PIN, SERVO_DELAY_MS);
//SPS_RFID_Scanner exitScanner(RFID_EXIT_SS_PIN, RFID_ENTER_RST_PIN);
SPS_RFID_Scanner entryScanner(RFID_ENTER_SS_PIN, RFID_ENTER_RST_PIN);

bool hasSlot;
int slotStates[TOTAL_SLOTS];

bool isEntryFrontSensorDetected;
bool isEntryBackSensorDetected;
bool isExitFrontSensorDetected;
bool isExitBackSensorDetected;

bool isValidCardDetectedEntry;
//bool isValidCardDetectedExit;

bool currentEntryGateStatus;
bool currentExitGateStatus;

void setup() {
  Serial.begin(9600);
  hasSlot = true;

  isEntryFrontSensorDetected = false;
  isEntryBackSensorDetected = false;
  isExitFrontSensorDetected = false;
  isExitBackSensorDetected = false;

  isValidCardDetectedEntry = false;

  unsigned char** validUIDs = new unsigned char*[6];  // 6 rows

  // Allocate memory for each row and populate the array
  validUIDs[0] = new unsigned char[4]{ 0x6D, 0xE2, 0xD7, 0x21 };  // Thẻ 1
  validUIDs[1] = new unsigned char[4]{ 0x23, 0x0A, 0x54, 0x11 };  // Thẻ 2
  validUIDs[2] = new unsigned char[4]{ 0xE3, 0x9A, 0x66, 0x10 };  // Thẻ 3
  validUIDs[3] = new unsigned char[4]{ 0x43, 0x34, 0x54, 0x10 };  // Thẻ 4
  validUIDs[4] = new unsigned char[4]{ 0x40, 0x1E, 0x4A, 0x12 };  // Thẻ 5
  validUIDs[5] = new unsigned char[4]{ 0x6A, 0xD5, 0x17, 0xA4 };  // Thẻ 6

  infraredSensor.init();
  display.init();
  entryGate.init();
  entryScanner.init(validUIDs, 6);
  exitGate.init();
  //exitScanner.init(validUIDs, 6);
}

void loop() {
  readSensor();
  render();

  if (currentEntryGateStatus == OPEN) {
    entryGate.open();
  } else {
    entryGate.close();
  }

  if (currentExitGateStatus == OPEN) {
    exitGate.open();
  } else {
    exitGate.close();
  }
}

void updateEntryGateStatus() {
  if (currentEntryGateStatus == OPEN) {
    if (!isEntryFrontSensorDetected && !isEntryBackSensorDetected) {
      currentEntryGateStatus = CLOSE;
      entryScanner.clearCache();
    }
  } else {
    if (hasSlot && isValidCardDetectedEntry && isEntryFrontSensorDetected) {
      currentEntryGateStatus = OPEN;
    } else {
      currentEntryGateStatus = CLOSE;
      entryScanner.clearCache();
    }
  }
}

void updateExitGateStatus() {
  if (currentExitGateStatus == OPEN) {
    if (!isExitFrontSensorDetected && !isExitBackSensorDetected) {
      currentExitGateStatus = CLOSE;
      //exitScanner.clearCache();
    }
  } else {
    if (isExitFrontSensorDetected) {
      currentExitGateStatus = OPEN;
    } else {
      currentExitGateStatus = CLOSE;
      //exitScanner.clearCache();
    }
  }
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

  isValidCardDetectedEntry = entryScanner.isCardValid();
  //isValidCardDetectedExit = exitScanner.isCardValid();

  updateEntryGateStatus();
  updateExitGateStatus();
}

void render() {
  display.render(slotStates[0], slotStates[1], slotStates[2], slotStates[3], slotStates[4], slotStates[5]);
}
