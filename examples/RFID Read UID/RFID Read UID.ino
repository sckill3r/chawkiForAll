#include <chawkiForAll.h>
#define SS_PIN 11
#define RST_PIN 12

chawkiForAll all;

void setup() {
  all.initRFID(SS_PIN, RST_PIN);

}

void loop() {
   String cardUID;
   
  if (all.readRFID(cardUID)) {
    Serial.print("Card ID: ");
    Serial.println(cardUID);
  }

}
