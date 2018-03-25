// Timestamp library
#include <TimeLib.h>
#include <Time.h>

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

void setColor(int red, int green, int blue) {
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
// debugging loop
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Puppet Guest", "argon4949");
  
  // get input from MiCS5524 sensor
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1200);  // To freeze the upper limit
  Serial.print(" ");

  // send input to switch table via sample variable
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

  // monitor via Serial Plotter tool
  Serial.println(reading);

  // switch colors based on sample reading
  // roughly equivalent to 
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
      //Very Unhealthy: Purple
      setColor(900, 0, 1023);
      delay(2000);
      break;

    case 5:
      //Hazardous: Blue
      setColor(0, 0, 1023);
      delay(2000);
  }

  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    
    http.begin("http://10.0.12.158:3000"); //HTTP

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header

    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["timeStamp"]=now();
    JSONencoder["AQI"] = reading;

    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
    
    http.begin("http://10.0.12.158:3000");

    int httpCode = http.POST(JSONmessageBuffer);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
      }
    //http.addHeader("Content-Type", "application/json");
    //int httpCode = http.POST("message from ");cd 
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } 
  delay(10000);
      
}

