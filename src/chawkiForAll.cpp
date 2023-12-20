#include "chawkiForAll.h"

chawkiForAll::chawkiForAll() {
	dht = nullptr; 
    lcd = nullptr;
}

void chawkiForAll::initDHT(uint8_t pin, uint8_t type) {
  dht = new DHT(pin, type);
  dht->begin();
}

float chawkiForAll::readTemperature() {
  if (dht != nullptr) {
    return dht->readTemperature(); // Use arrow operator to access member function
  }
  return NAN;
}

float chawkiForAll::readHumidity() {
  if (dht != nullptr) {
    return dht->readHumidity(); // Use arrow operator to access member function
  }
  return NAN;
}
void chawkiForAll::initDistance(uint8_t trigPin, uint8_t echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float chawkiForAll::measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  return (duration / 2) * 0.0343;
}

void chawkiForAll::initLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows) {
  lcd = new LiquidCrystal_I2C(lcd_addr, lcd_cols, lcd_rows);
  lcd->begin();
  lcd->backlight();
}

void chawkiForAll::displayMessage(const char* line1, const char* line2) {
  if (lcd != nullptr) {
    lcd->setCursor(0, 0); 
    lcd->print(line1);    
    lcd->setCursor(0, 1); 
    lcd->print(line2);    
  }
}

void chawkiForAll::clearLCD() {
  lcd->clear();
}

void chawkiForAll::initWiFi(const char* ssid, const char* password) {
  this->ssid = ssid;
  this->password = password;
  WiFi.begin(ssid, password);
}

bool chawkiForAll::connectToWiFi() {
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 10) {
    delay(1000);
    attempt++;
  }
  
  return WiFi.status() == WL_CONNECTED;
}

void chawkiForAll::initRFID(uint8_t rfidSDAPin, uint8_t rfidRSTPin) {
  mfrc522 = MFRC522(rfidSDAPin, rfidRSTPin);
  mfrc522.PCD_Init();
}

bool chawkiForAll::readRFID(String& cardUID) {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    return true;
  }
  return false;
}
