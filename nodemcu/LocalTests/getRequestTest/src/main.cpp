#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// !
#include "password.h"

uint8_t pin = D4;

void setup()
{
    // ? Pins    
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    // ? Serial 
    Serial.begin(9600);
    while(!Serial);

    // ? WiFi
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println();
    Serial.printf("LocalIP: %s\n", WiFi.localIP().toString().c_str());

    // ? HTTP Connection
    Serial.println("Starting HTTP GET Request");
    HTTPClient http;

    http.begin("http://192.168.29.186:1337/parse/classes/Test");
    http.addHeader("X-Parse-Application-Id", "myAppId");
    http.addHeader("Content-Type", "application/json");

    int status = http.GET();
    Serial.printf("Status: %d\n", status);

    if(status > 0)
    {
        String payload = http.getString();
        Serial.println(payload);
    }
    http.end();
    Serial.println("Ended HTTP GET Request");
}

void loop() 
{
    // put your main code here, to run repeatedly:
}
