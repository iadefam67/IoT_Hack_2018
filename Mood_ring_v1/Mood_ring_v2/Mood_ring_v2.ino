#include <ArduinoJson.h>

// Timestamp library
#include <TimeLib.h>

// ok to remove?
//#include <Time.h>

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
int count = 0;
int baseline = 250;

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
  for (uint8_t t = 4; t > 0; t--) {
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
// sensor callibration 
int sample_baseline() {
    setColor(0, 0, 1023);
    delay(30000);
    int avg = 0;
    setColor(1023, 0, 0);
    for (int i = 0; i < 60; ++i) {
      avg += analogRead(A0);
      delay(100);
    }
    avg = avg/60;
    Serial.println(avg);
    return avg; 
}

void loop() {
  
  if (count == 0) {
    baseline = sample_baseline();
  }
  count = 1;

  // send input to switch table via sample variable
  int reading = analogRead(A0);
  
  if (reading < baseline) {
    sample = 0;
  }
  if (reading > baseline && reading <= (baseline + 25)) {
    sample = 1;
  }
  if (reading > (baseline + 25) && reading <= (baseline + 50)) {
    sample = 2;
  }
  if (reading > (baseline + 50) && reading <= (baseline + 100)) {
    sample = 3;
  }
  if (reading > (baseline + 100) && reading <= (baseline + 200)) {
    sample = 4;
  }
  if (reading > (baseline + 200)) {
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
      break;

    case 1:
      //Moderate: Yellow
      setColor(1023, 1023, 0);    
      break;

    case 2:
      //Unhealthy for Sensitive Groups (USG): Orange
      setColor(1023, 300, 100);
     
      break;

    case 3:
      //Unhealthy: Red
      setColor(1023, 0, 0);
     
      break;

    case 4:
      //Very Unhealthy: Purple
      setColor(900, 0, 1023);
     
      break;

    case 5:
      //Hazardous: Blue
      setColor(0, 0, 1023);
     
  }

  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url

    USE_SERIAL.print("[HTTP] POST...\n");
    // start connection and send HTTP header

    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["timeStamp"] = "0";
    JSONencoder["AQI"] = sample;
    JSONencoder["location"] = 0;
    JSONencoder["status"] = 0;

    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

    http.begin("http://10.0.12.158:3000/api/aqi");
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(JSONmessageBuffer);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
//      if (httpCode == HTTP_CODE_OK) {
//        String payload = http.getString();
//        USE_SERIAL.println(payload);
//      }
      //http.addHeader("Content-Type", "application/json");
      //int httpCode = http.POST("message from ");cd
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  delay(100);

}

