/*
 * IoT Button example
 *
 * This example subscribe to the "button" topic. When a message received, then it
 * will show the message
 *
 * Created 21 Febuary 2018 by Mallor Kingsepp
 */
 
// Includes global variables and librarys that the Buzzer uses
#include <Arduino.h>
#include <ittiot.h>
#include <Switch.h>
#include <ESP8266WiFi.h>
 
#define WIFI_NAME "11T Pro"
#define WIFI_PASSWORD "Io376256"
 
const byte buttonPin = D3; // TO which pin the button has been assigned
int i;
 
Switch button = Switch(buttonPin);
 
void iot_received(String topic, String msg) {}
 
// Function started after the connection to the server is established.
void iot_connected()
{
  Serial.println("MQTT connected callback");
  iot.log("IoT Button example!");
}
 
void setup()
{
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");
 
  pinMode(buttonPin, INPUT);
  
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.printConfig(); // Print json config to serial
  iot.setup(); // Initialize IoT library
}
 
void loop()
{
  // IoT behind the plan work, it should be periodically called
  iot.handle();
 
  // Askes in which state the button is, pressed, long pressed, double click, or released.
  button.poll();
 
  // If the button is long pressed, it publishes message “LongPressed”
  if (button.longPress()) {
    iot.log("LongPressed");
  }
 
  // If the button is double clicked, it publishes message “DoubleClick”
  if (button.doubleClick()) {
     iot.log("DoubleClick");
  }
 
  // If the button has been released, it publishes message “Released”
  if (button.released()) {
    iot.log("Released");
    String msg = String("0");
    iot.publishMsg("butt1", msg.c_str());
    Serial.println(msg);
  }
 
  // If the button is pushed down, it publishes message “ButtonPushed”
  if (button.pushed()) {
    iot.log("ButtonPushed");
    String msg = String("1");
    iot.publishMsg("butt1", msg.c_str());
    Serial.println(msg);
  }
 
  delay(3);
}