#include <chawkiForAll.h>
const char *firebaseHost = "your Firebase link";
const char *databaseSecret = "your Firebase key";
chawkiForAll all;

  String message;
  int temperature;
  float humidity;
  bool status;
  double precision;
  
void setup() {
  Serial.begin(9600);
  // wifi
  all.initWiFi("SSID", "PASSWORD");
  all.connectToWiFi();
  Serial.println("Connected to WiFi!");

  // initiate firebase
  all.initFb(firebaseHost,databaseSecret );
   
}

void loop() {

  //Set To Firebase

  all.setFbInt("path/temperature", 25);
  all.setFbFloat("path/humidity", 60.5);
  all.setFbString("path/message", "Hello from Firebase!");
  all.setFbBool("path/status", true);
  all.setFbDouble("path/precision", 3.14159);

  //Get from Firebase

  all.getFbString("path/message", message);
  all.getFbInt("path/temperature", temperature);
  all.getFbFloat("path/humidity", humidity);
  all.getFbBool("path/status", status);
  all.getFbDouble("path/precision", precision);

  //Printing to serial 

  Serial.println("Received from Firebase:");
  Serial.print("Message: ");
  Serial.println(message);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Status: ");
  Serial.println(status ? "true" : "false");
  Serial.print("Precision: ");
  Serial.println(precision);

  delay(2000);
}
