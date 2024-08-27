#ifndef Display_H
#define Display_H

#include <LiquidCrystal_I2C.h>

enum SlotStatus
{
    FILL,
    EMPTY
};

class Display
{
public:
    Display();
    void init();
    void render();
    void updateSlot(int slot, SlotStatus status);
private:
    LiquidCrystal_I2C lcd;
};

#endif