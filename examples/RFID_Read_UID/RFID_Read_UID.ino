#include <chawkiForAll.h>
#define SS_PIN 11
#define RST_PIN 12

chawkiForAll all;

String cardUID;

void setup() {
  all.initRFID(SS_PIN, RST_PIN);

}

void loop() {
   
  if (all.readRFID(cardUID)) {
    Serial.print("Card ID: ");
    Serial.println(cardUID);
  }

}
