
#include <WiFi.h>  // Bibliothèque wifi pour esp32

#include <FirebaseESP32.h>  // Bibliothèque firebase
#include <FirebaseArduino.h> 
#define FIREBASE_HOST "esp32-c38ff-default-rtdb.firebaseio.com/"        // adresse de la base de données dans Firebase
#define FIREBASE_AUTH "CFKNuVQZ9qmCePpOYJInlnwk8JffBCmPS0DlqV3Y"            // Code secret de la base de données
#define WIFI_SSID "TOPNET_1570"                     
#define WIFI_PASSWORD "yvbm84z2d9"  
#include "PZEM004T.h"                                 
 
PZEM004T pzem(&Serial);
  
void setup() {
  
 Serial.begin(115200);

 
  delay(1000);
                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                  //essai de connexion wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 serial.println();
 serial.print("connecting : ");
 serial.println(Wifi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 

}

void loop() {
   float voltage = pzem.voltage();
    if(!isnan(voltage)){
        Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
    } else {
        Serial.println("Error reading voltage");
    }

    float current = pzem.current();
    if(!isnan(current)){
        Serial.print("Current: "); Serial.print(current); Serial.println("A");
    } else {
        Serial.println("Error reading current");
    }

    float power = pzem.power();
    if(!isnan(power)){
        Serial.print("Power: "); Serial.print(power); Serial.println("W");
    } else {
        Serial.println("Error reading power");
    }

    float energy = pzem.energy();
    if(!isnan(energy)){
        Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
    } else {
        Serial.println("Error reading energy");
    }

 Firebase.setFloat("number",voltage); 
 if (Firebase.failed()) { 
     Serial.print("setting /number failed:"); 
     Serial.println(Firebase.error());   
     return;
      Firebase.setString("message", "hello world"); 
 // handle error 
 if (Firebase.failed()) { 
     Serial.print("setting /message failed:"); 
     Serial.println(Firebase.error());   
     return; 
 } 
 delay(1000);   


}
