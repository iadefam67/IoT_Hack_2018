#define LED LED_BUILTIN
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
// LED global vars
int redPin = 4;
int greenPin = 5;
int bluePin = 2;
// Input sample
int sample;

void setColor(int red, int green, int blue)
{
  red = 1023 - red;
  green = 1023 - green;
  blue = 1023 - blue;

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Mood Ring Demo");

  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSID", "PASSWORD");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1200);  // To freeze the upper limit
  Serial.print(" ");

  int reading = analogRead(A0);
  if (reading < 200) {
    sample = 0;
  }
  if (reading > 200 && reading <= 250) {
    sample = 1; 
  }
  if (reading > 250 && reading <= 300) {
    sample = 2;
  }
  if (reading > 300 && reading <= 350) {
    sample = 3;  
  }
  if (reading > 350 && reading <= 700) {
    sample = 4;
  }
  if (reading > 700) {
    sample = 5;
  }

  
  Serial.println(reading);

    switch (sample) {

      case 0:
        //Good: Green
        setColor(0, 1023, 0);
        delay(2000);
        break;

      case 1:
        //Moderate: Yellow
        setColor(1023, 1023, 0);
        delay(2000);
        break;

      case 2:
        //Unhealthy for Sensitive Groups (USG): Orange
        setColor(1023, 300, 100);
        delay(2000);
        break;

      case 3:
        //Unhealthy: Red
        setColor(1023, 0, 0);
        delay(2000);
        break;

      case 4:
        //Very Unhealthy: Light Purple
        setColor(900, 0, 1023);
        delay(2000);
        break;

      case 5:
        //Hazardous: Blue
        setColor(0, 0, 1023);
        delay(2000);
    }
}

