#include "Display.h"

Display::Display() : lcd(0x27, 20, 4) {}

void Display::init()
{
    lcd.init();
    lcd.backlight();
}

void Display::render()
{
    lcd.clear();

    lcd.setCursor(4, 0);
    lcd.print("Have slot: 2");

    lcd.setCursor(0, 1);
    lcd.print("S1:Fill");
    lcd.setCursor(12, 1);
    lcd.print("S2:Fill");

    lcd.setCursor(0, 2);
    lcd.print("S3:Empty");
    lcd.setCursor(12, 2);
    lcd.print("S4:Empty");

    lcd.setCursor(0, 3);
    lcd.print("S5:Fill");
    lcd.setCursor(12, 3);
    lcd.print("S6:Fill");
}