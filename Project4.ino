#include <WiFi.h>

#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://projectiot4-8363d-default-rtdb.firebaseio.com/"
#define FIREBASE_SECRET "NCtSmvSuAgLXLEvfQEbmb6CAD2m0co58Aa0Gs3Oo"
#define WIFI_SSID "wolverine"
#define WIFI_PASSWORD "tanpapassword"

#define buzzer 12
#define ldr 36

FirebaseData fbd;
FirebaseAuth auth;
FirebaseConfig config;

String path = "/Node1";

                
unsigned long dataMillis = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(buzzer,OUTPUT);
    pinMode(ldr,INPUT);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the certificate file (optional) */
    //config.cert.file = "/cert.cer";
    //config.cert.file_storage = StorageType::FLASH;

    /* Assign the database URL and database secret(required) */
    config.database_url = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_SECRET;

    Firebase.reconnectWiFi(true);

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

    //Or use legacy authenticate method
    //Firebase.begin(FIREBASE_HOST, FIREBASE_SECRET);
    
   
}
void loop()
{
  String power;
  String on = "ON";
  if (millis() - dataMillis > 2000)
  {
      Firebase.getString(fbd,"/Node1/Power");
      power = fbd.stringData();
      dataMillis = millis();
      Serial.print("Power: ");
      Serial.print(power);
      Serial.println();
      int ldrValue = analogRead(ldr);
      Serial.print("LDR: ");
      Serial.print(ldrValue);
      Serial.println();
      if (Firebase.setFloat(fbd, "/Node1/LDR", ldrValue))
      {
        Serial.print(fbd.dataPath());
        Serial.print(fbd.dataType());
        Serial.println();
      }
      else
      {
        Serial.print(fbd.errorReason());
        Serial.println();
      }
      if(ldrValue == 0){
        digitalWrite(buzzer,LOW);
      } else {
        digitalWrite(buzzer,HIGH);
      }
      delay(100);   
}
}
