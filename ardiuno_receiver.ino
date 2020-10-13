
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> 
#endif
RH_ASK rf_driver(2000,2, 4, 5); 

#define FIREBASE_HOST "****************"                         // the project name address from firebase id
#define FIREBASE_AUTH "************"                    // the secret key generated from firebase
#define WIFI_SSID "***********"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "***************"                                    //password of wifi ssid


void setup()
{
    Serial.begin(9600);
  if(rf_driver.init()){
    Serial.print("iniit failed");
   };
     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
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
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
}
 
void loop()
{
    uint8_t buf[RH_ASK_MAX_PAYLOAD_LEN];
    delay(1000);
    uint8_t buflen = sizeof(buf);
    
      if (rf_driver.recv(buf, &buflen)) // Non-blocking
   {
    rf_driver.printBuffer("Got:", buf, buflen);
    delay(2000);
    Serial.println((char*)buf); 
    String str = String((char*)buf);
    delay(2000);  
    String Latitude = str.substring(0,6);
    delay(2000); 
    String Longitude = str.substring(7,14);
    delay(2000);  
    delay(1000);   
    Firebase.setString("EmergencyLocation/123456789/Latitude",Latitude);
    delay(2000); 
    Firebase.setString("EmergencyLocation/123456789/Longitude",Longitude);
    delay(2000); 
    Firebase.setString("EmergencyLocation/123456789/UserID","123456789");
    delay(68000);
   }
}
