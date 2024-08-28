#ifndef SPS_GateControl_H
#define SPS_GateControl_H

#include <SPI.h>
#include <MFRC522.h>

class SPS_GateControl
{
public:
    /**
     * @param   RST_PIN
     * @param   SS_PIN
     */
    SPS_GateControl(int SS_PIN, int RST_PIN);

    /**
     * Check if the card is valid
     */
    bool checkUID();

    /**
     * Read the UID of the card
     */
    void readCard();

    /**
     * Setup RFID RC522 connection. Must be called before using other functions
     */
    void init();

private:
    MFRC522 rfid;
    byte validUIDs[4][4] = {
        {0x23, 0x0A, 0x54, 0x11},  // Thẻ 1
        {0xE3, 0x9A, 0x66, 0x10},  // Thẻ 2
        {0x40, 0x1E, 0x4A, 0x12},  // Thẻ 3
        {0x43, 0x34, 0x54, 0x10}   // Thẻ 4
    };
};

#endif