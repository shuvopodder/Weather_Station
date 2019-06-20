//#include <FirebaseArduino.h> 
#include <IOXhop_FirebaseESP32.h>  
#include <WiFi.h>              
#include "DHT.h"

#define FIREBASE_HOST "https://test-20c83.firebaseio.com/"      // Project name address from firebase id
#define FIREBASE_AUTH "ttPqoGm5jvZ1wNdxR5UMdEa6gRIgzdmSwDltX9nw"            //  Secret key generated from firebase

#define WIFI_SSID "shuvo"                                     // Enter your wifi name
#define WIFI_PASSWORD "123456789"                  //Enter your wifi password

 
#define DHTPIN A13                                                          // Digital pin connected to DHT11
#define DHTTYPE DHT11                                                       // Initialize dht type as DHT 11
DHT dht(DHTPIN, DHTTYPE);                                                    

void setup() {

  Serial.begin(115200);

  delay(500);               

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  

  Serial.print("Connecting to ");

  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

  }

  Serial.println();

  Serial.print("Connected to ");

  Serial.println(WIFI_SSID);

  Serial.print("IP Address is : ");

  Serial.println(WiFi.localIP());                               // Will print local IP address

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);             // connect to firebase

  dht.begin();                                        //Start reading dht sensor

}


void loop() {

  float h = dht.readHumidity();                                 // Reading Humidity
  float t = dht.readTemperature();                           // Read temperature as Celsius
   
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed.
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h);                                         //convert integer humidity to string humidit
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t);                                                     //convert integer temperature to string temperature
  delay(4000);


  Firebase.pushString("Humidity", fireHumid);                                  //setup path and send readings
  Firebase.pushString("Temperature", fireTemp);                                //setup path and send readings

    if (Firebase.failed()) {

      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 

      return;

  }

}
