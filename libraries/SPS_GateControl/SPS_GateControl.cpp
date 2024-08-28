#include "SPS_GateControl.h"
#include <Arduino.h>

SPS_GateControl::SPS_GateControl(int SS_PIN, int RST_PIN) : rfid(SS_PIN, RST_PIN)
{
}

void SPS_GateControl::init()
{
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("RFID Reader Ready!");
}

void SPS_GateControl::readCard()
{
    if (!rfid.PICC_IsNewCardPresent()) {
        return;
    }

    if (!rfid.PICC_ReadCardSerial()) {
        return;
    }

    if (checkUID()) {
        Serial.println("Valid Card!");
    } else {
        Serial.println("Invalid Card!");
    }

    rfid.PICC_HaltA();
}

bool SPS_GateControl::checkUID()
{
    for (int i = 0; i < 4; i++) {
        if (rfid.uid.size != sizeof(validUIDs[i])) {
            continue;
        }

        bool match = true;
        for (byte j = 0; j < rfid.uid.size; j++) {
            if (rfid.uid.uidByte[j] != validUIDs[i][j]) {
                match = false;
                break;
            }
        }

        if (match) {
            return true;
        }
    }

    return false;
}
