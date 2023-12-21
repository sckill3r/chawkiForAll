#include <chawkiForAll.h>
#define DHT_PIN 7
#define DHT_TYPE DHT11

chawkiForAll all;

void setup() {
  Serial.begin(9600);
  all.initDHT(DHT_PIN, DHT_TYPE);
}

void loop() {
  float temperature = all.readTemperature();
  float humidity = all.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  delay(2000);
}
