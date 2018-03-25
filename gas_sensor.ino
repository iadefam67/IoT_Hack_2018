#include <TimeLib.h>
#include <Time.h>

#include <ArduinoJson.h>

#define LED LED_BUILTIN
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>


#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Puppet Guest", "argon4949");
}
 
void loop() {
  int reading = analogRead(A0);
  //Serial.println(reading);
  Serial.println("in loop");
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

