#include <chawkiForAll.h>

chawkiForAll all;

void setup() {
  all.initLCD(0x27,16,2);

}

void loop() {
  all.displayMessage("Hello", "World"); // (line1,line2)
  delay(2000);
  all.clearLCD();
  delay(2000);
}
