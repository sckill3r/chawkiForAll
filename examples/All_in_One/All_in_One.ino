#include <chawkiForAll.h>

chawkiForAll all;

#define DHT_PIN 5
#define DHT_TYPE DHT22

#define TRIG_PIN 6
#define ECHO_PIN 7


#define SSID "your_SSID"
#define PASSWORD "your_PASSWORD"

#define RFID_SDA_PIN 11
#define RFID_RST_PIN 12

void setup() {
  Serial.begin(9600);
  all.initDHT(DHT_PIN, DHT_TYPE);
  all.initDistance(TRIG_PIN, ECHO_PIN);
  all.initLCD(0x27,16,2);
  all.initWiFi(SSID, PASSWORD);
  all.initRFID(RFID_SDA_PIN, RFID_RST_PIN);
}

void loop() {
  float temperature = all.readTemperature();
  float humidity = all.readHumidity();
  float distance = all.measureDistance();

  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  Serial.print("Humidity: ");
  Serial.println(humidity);
  
  Serial.print("Distance: ");
  Serial.println(distance);

  String cardUID;
  if (all.readRFID(cardUID)) {
    Serial.print("Card ID: ");
    Serial.println(cardUID);
  }

  all.displayMessage("Hello", "World"); // (line1,line2)
  delay(2000);
  all.clearLCD();
  delay(2000);
}
