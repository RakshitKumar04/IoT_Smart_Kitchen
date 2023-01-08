#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>
#include <SPI.h>
#include <Wire.h>
#include <MQ135.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <ThingSpeak.h>


/*WiFi Credentials */
const char* ssid = "Smart Kitchen";  //WiFi Name
const char* password = "123456789";  //Password

#define DHTTYPE DHT11  //DHT 11
#define DHTPIN D1      //DHT11 Pin D1
#define relay1 D4      //Light D4
#define led D5         //led D5
#define buzzer D3      //Buzzer Pin D3
#define PIR D0         //PIR Sensor Pin D0
// #define MQ135 D2

int alarm_status;
int pir_status = 0;
WiFiClient client;
long myChannelNumber = 1872370;
String myAPIKey = "6XQ3ZCY54J8XV54B";

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
ESPDash dashboard(&server);
Card AIQ(&dashboard, GENERIC_CARD, "Air Quality Index", "PPM");
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");
Card light(&dashboard, BUTTON_CARD, "Light");
Card Buzzer(&dashboard, STATUS_CARD, "Buzzer");
Card Motion_PIR(&dashboard, STATUS_CARD, "Human");


void setup() {
  Serial.begin(115200);
  /* Connect WiFi */
  WiFi.softAP(ssid, password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  /* Start AsyncWebServer */
  server.begin();

  dht.begin();
  ThingSpeak.begin(client);
  
  pinMode(PIR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(led, OUTPUT);
  // pinMode(MQ135,INPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(relay1, HIGH);
  digitalWrite(led, LOW);

  delay(10);
}

void loop() {
  /* Update Card Values */
  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  int airQ = analogRead(A0);
  // Serial.println("air quality = ");
  // Serial.println(airQ);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

 ThingSpeak.writeField(myChannelNumber, 1, t, myWriteApiKey);
 ThingSpeak.writeField(myChannelNumber, 2, h, myWriteApiKey);

  pir_status = digitalRead(PIR);
  alarm_status = digitalRead(buzzer);


  if (pir_status == 1) {
    Serial.println("Motion Detected");
    Motion_PIR.update("Motion Detected", "success");
    dashboard.sendUpdates();
    digitalWrite(led, HIGH);

  } else if (pir_status == 0) {
    Serial.println("Motion not Detected");
    Motion_PIR.update("Motion not Detected", "danger");
    dashboard.sendUpdates();
    digitalWrite(led, LOW);
  }


  if (airQ > 7) {
    digitalWrite(buzzer, HIGH);
    // digitalWrite(relay4, LOW);
    Serial.println("Buzzer Status: ON");
    // Serial.println("Exhaust Fan: ON");
    Buzzer.update("ON", "warning");
    // fan.update(HIGH);
    dashboard.sendUpdates();
  } else {
    digitalWrite(buzzer, LOW);
    // digitalWrite(relay4, HIGH);
    Serial.println("Buzzer Status: OFF");
    // Serial.println("Exhaust Fan: OFF");
    Buzzer.update("OFF", "success");
    // fan.update(LOW);
    dashboard.sendUpdates();
  }

  Serial.print("Air Quality: ");
  Serial.print(airQ);
  Serial.println(" PPM");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  Serial.println();
  Serial.println("****************************");
  Serial.println();

  temperature.update(t);
  humidity.update(h);
  AIQ.update(airQ);

  //Button for Light
  light.attachCallback([&](bool value) {
    Serial.println("[light] Button Callback Triggered: " + String((value) ? "LOW" : "HIGH"));
    digitalWrite(relay1, (value));
    light.update(value);
    dashboard.sendUpdates();
  });
  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();
  delay(1000);
}