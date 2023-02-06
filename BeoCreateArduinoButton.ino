#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
String mainURL ="http://beocreate.local/interact/trigger/";

int firstKeyPin = 14;
int secondKeyPin = 12;
int thirdKeyPin = 13;

void setup() {
  Serial.begin(115200);
  Serial.print("setup");
  //set the button pins as inputs
  pinMode(firstKeyPin, INPUT_PULLUP);
  pinMode(secondKeyPin, INPUT_PULLUP);
  pinMode(thirdKeyPin, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ssid", "password");
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.localIP());

    if (digitalRead(firstKeyPin) == LOW) {      //if the first key is pressed
      Serial.print("Button Red Pressed");  
      Serial.println();
      beocreate("mute");
      delay(200); // waits for half a second
    }
    else if (digitalRead(secondKeyPin) == LOW) { //if the second key is pressed
      Serial.print("Button Yellow Pressed");  
      Serial.println();
      beocreate("volup");    
      delay(200); // waits for half a second
    }
   else if (digitalRead(thirdKeyPin) == LOW) { //if the third key is pressed
      Serial.print("Placeholder");  
      Serial.println();
      beocreate("voldown");
      delay(200); // waits for half a second
   }
  } else {
    Serial.println("WiFi not connected!");
  } 
} 

void beocreate(char* arg)  {
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...");
    if (http.begin(client, mainURL + arg)) {  // HTTP
        http.addHeader("Content-Type", "text/plain");  //Specify content-type header
        int httpCode = http.POST(arg);   //Send the request
        String payload = http.getString();                  //Get the response payload
        Serial.println(httpCode);   //Print HTTP return code
        Serial.println(payload);    //Print request response payload
        http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect");
    }
}
