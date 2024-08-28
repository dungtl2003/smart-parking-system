#include <SPS_Display.h>

SPS_Display display(0x27, 45);

void setup() {
  display.init();
}

void loop() {
  // Your loop code here
  display.render(1, 1, 0, 1, 0, 0);
}