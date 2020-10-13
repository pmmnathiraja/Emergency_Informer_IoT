#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;


char junk;
String inputString="";

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  if(Serial.available()){
    while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;  
      delay(5);//make a string of the characters coming on serial
    }
         while (Serial.available() > 0)  
    { junk = Serial.read() ; } 
  }
    inputString = "**************";
    int str_len = inputString.length() + 1; 
    char msg[str_len];
    Serial.println(inputString);
    inputString.toCharArray(msg, str_len);
    Serial.println((char*)msg);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(3000);
    Serial.println((char*)msg);
    delay(1000);
   inputString = "";  
  
}
