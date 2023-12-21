#include "chawkiForAll.h"

#ifdef ARDUINO_ARCH_ESP32 
  #include "WiFi.h" 
  #include "FirebaseESP32.h"
#endif

#ifdef ARDUINO_ARCH_ESP8266 
  #include "ESP8266WiFi.h" 
  #include "FirebaseESP32.h"
#endif
FirebaseData firebaseData;
chawkiForAll::chawkiForAll() {
	dht = nullptr; 
    lcd = nullptr;
    firebaseInitialized = false;
}

void chawkiForAll::initDHT(uint8_t pin, uint8_t type) {
  dht = new DHT(pin, type);
  dht->begin();
}

float chawkiForAll::readTemperature() {
  if (dht != nullptr) {
    return dht->readTemperature();
  }
  return NAN;
}

float chawkiForAll::readHumidity() {
  if (dht != nullptr) {
    return dht->readHumidity();
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
  return (duration / 2) * 0.0340;
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
  if (lcd != nullptr) {
    lcd->clear();
  }
}

void chawkiForAll::initWiFi(const char* ssid, const char* password) {
  this->ssid = ssid;
  this->password = password;
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  WiFi.begin(ssid, password);
  #endif
}

bool chawkiForAll::connectToWiFi() {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
	int attempt = 0;
	while (WiFi.status() != WL_CONNECTED && attempt < 10) {
		delay(1000);
		attempt++;
  }
  
	return WiFi.status() == WL_CONNECTED;
  #else
    return false;
  #endif
}

void chawkiForAll::initFb(const char* firebaseHost, const char* databaseSecret) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  Firebase.begin(firebaseHost, databaseSecret);
  firebaseInitialized = true;
  #endif
}

bool chawkiForAll::setFbInt(const char* path, int value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    Firebase.setInt(firebaseData, path, value);
    return true;
  }
  #endif
  return false;
}

bool chawkiForAll::setFbFloat(const char* path, float value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    Firebase.setFloat(firebaseData, path, value);
    return true;
  }
  #endif
  return false;
}

bool chawkiForAll::setFbString(const char* path, const char* value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    Firebase.setString(firebaseData, path, value);
    return true;
  }
  #endif
  return false;
}

bool chawkiForAll::setFbBool(const char* path, bool value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    Firebase.setBool(firebaseData, path, value);
    return true;
  }
  #endif
  return false;
}

bool chawkiForAll::setFbDouble(const char* path, double value) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
    if (firebaseInitialized) {
        Firebase.setDouble(firebaseData, path, value);
        return true;
    }
    #endif
    return false;
}

bool chawkiForAll::getFbString(const char* path, String& value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    if (Firebase.getString(firebaseData, path)) {
      value = firebaseData.stringData();
      return true;
    }
  }
  #endif
  return false;
}

bool chawkiForAll::getFbInt(const char* path, int& value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    if (Firebase.getInt(firebaseData, path)) {
      value = firebaseData.intData();
      return true;
    }
  }
  #endif
  return false;
}

bool chawkiForAll::getFbFloat(const char* path, float& value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    if (Firebase.getFloat(firebaseData, path)) {
      value = firebaseData.floatData();
      return true;
    }
  }
  #endif
  return false;
}

bool chawkiForAll::getFbBool(const char* path, bool& value) {
  #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
  if (firebaseInitialized) {
    if (Firebase.getBool(firebaseData, path)) {
      value = firebaseData.boolData();
      return true;
    }
  }
  #endif
  return false;
}

bool chawkiForAll::getFbDouble(const char* path, double& value) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
    if (firebaseInitialized) {
        if (Firebase.getDouble(firebaseData, path)) {
            value = firebaseData.doubleData();
            return true;
        }
    }
    #endif
    return false;
}