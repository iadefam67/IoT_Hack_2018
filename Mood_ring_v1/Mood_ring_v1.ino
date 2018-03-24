#define LED LED_BUILTIN
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Serial.println("Mood Ring Demo");
  
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSID", "PASSWORD");
}
 
void loop() {
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1200);  // To freeze the upper limit
  Serial.print(" ");

  int reading = analogRead(A0);
  Serial.println(reading);

  digitalWrite(4, LOW);   
  delay(1000);              
  digitalWrite(4, HIGH);   
  delay(1000);  
}


