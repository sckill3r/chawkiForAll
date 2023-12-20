#ifndef chawkiForAll_h
#define chawkiForAll_h

#include "Arduino.h"
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#include <MFRC522.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

class chawkiForAll {
  public:
    chawkiForAll();
    void initDHT(uint8_t pin, uint8_t type);
    float readTemperature();
    float readHumidity();
    void initDistance(uint8_t trigPin, uint8_t echoPin);
    float measureDistance();
    void initLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);
	void clearLCD();
    void displayMessage(const char* line1, const char* line2);
    void initWiFi(const char* ssid, const char* password);
    bool connectToWiFi();
    void initRFID(uint8_t rfidSDAPin, uint8_t rfidRSTPin);
    bool readRFID(String& cardUID);

  private:
    DHT *dht;
    uint8_t trigPin;
    uint8_t echoPin;
    LiquidCrystal_I2C *lcd;
    const char* ssid;
    const char* password;
    MFRC522 mfrc522;
};

#endif
