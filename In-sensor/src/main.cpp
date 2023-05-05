/*
 * IoT PIR example
 *
 * This example subscribe to the "pir" topic. When a message received, then it
 * will switch the pir module "ON" and "OFF"
 *
 * Created 21 Febuary 2018 by Heiko Pikner and Mallor Kingsepp
 */
 
// Includes global variables and librarys that the PIR shield uses
#include <Arduino.h>
#include <ittiot.h>
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define MODULE_TOPIC "ESP05/pir"
#define WIFI_NAME "11T Pro"
#define WIFI_PASSWORD "Io376256"
 
//Pin definition for the PIR (GPIO14)
#define PIR_PIN D5
//Pin definition for the PIR LED (GPIO16)
#define PIR_LED_PIN D4
 
// PIR state for detection
bool pirState;
// State that switches PIR on and off
bool onState;
 
// If message received for PIR topic. For example:
// mosquitto_pub -u test -P test -t "ITT/IOT/3/pir" -m "1"
void iot_received(String topic, String msg)
{
}
 
// Function started after the connection to the server is established.
void iot_connected()
{
  Serial.println("MQTT connected callback");
  // Subscribe to the topic "pir"
  iot.subscribe(MODULE_TOPIC);
  iot.log("IoT PIR example!");
}
 
void setup()
{
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");
 
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.printConfig(); // Print json config to serial
  iot.setup(); // Initialize IoT library
 
  // Initialize PIR pin
  pinMode(PIR_PIN, INPUT);
  pinMode(PIR_LED_PIN, OUTPUT);
}
 
void loop()
{
  iot.handle(); // IoT behind the plan work, it should be periodically called
  delay(20); // Wait 0.02 seconds
  // This part of the code is executed, when PIR shield is active
  if(digitalRead(PIR_PIN))
  {
    if(pirState == false)
    {
      // When PIR has detected motion, then the LED is switched on and text “Motion detected!” is published to the MQTT broker
      digitalWrite(PIR_LED_PIN, HIGH);
      String msg = String("1");
      iot.publishMsg("Out", msg.c_str());
      Serial.println(msg);
      pirState = true;
    }
  }
  else
  {
    if(pirState == true)
    {
      // PIR shields LED is switched off, when it is not detecting any motion
      digitalWrite(PIR_LED_PIN, LOW);
      String msg = String("0");
      iot.publishMsg("Out", msg.c_str());
      Serial.println(msg);
      pirState = false;
    }
  }
}