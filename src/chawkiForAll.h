#ifndef chawkiForAll_h
#define chawkiForAll_h

#include "Arduino.h"
#include <DHT.h>
#include <screen_I2C.h>
#include <RFID.h>

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP32.h>
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

    void initFb(const char* firebaseHost, const char* databaseSecret);
#if defined(ESP32) || defined(ESP8266)
	bool setFbInt(const char* path, int value);
    bool setFbFloat(const char* path, float value);
    bool setFbString(const char* path, const char* value);
    bool setFbBool(const char* path, bool value);
    bool setFbDouble(const char* path, double value);
    bool getFbString(const char* path, String& value);
    bool getFbInt(const char* path, int& value);
    bool getFbFloat(const char* path, float& value);
    bool getFbBool(const char* path, bool& value);
    bool getFbDouble(const char* path, double& value);
#endif

  private:
    DHT *dht;
    uint8_t trigPin;
    uint8_t echoPin;
    screen_I2C *lcd;
    const char* ssid;
    const char* password;
    RFID rfid;
#if defined(ESP32) || defined(ESP8266)
    FirebaseData firebaseData;
    bool firebaseInitialized; 
#endif
};

#endif
