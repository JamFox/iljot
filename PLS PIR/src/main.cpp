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
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define DHT_TOPIC1 "ESP05"
#define DHT_TOPIC2 "ESP36"
#define DHT_TOPIC3 "ESP43"
#define WIFI_NAME "11T Pro"
#define WIFI_PASSWORD "Io376256"

//Pin definition for the Servo (D3)
#define SERVO_PIN            D3
 
Servo myservo;  // create servo object to control a servo

//Pin definition for the PIR (GPIO14)
#define PIR_PIN D5
//Pin definition for the PIR LED (GPIO16)
#define PIR_LED_PIN D4
 
// PIR state for detection
bool pirState;
// State that switches PIR on and off

bool full;
bool b1;
bool b2;
bool OutPir;
 
// If message received for PIR topic. For example:
// mosquitto_pub -u test -P test -t "ITT/IOT/3/pir" -m "1"
void iot_received(String topic, String msg)
{
  Serial.print("MSG FROM USER callback, topic: ");
  Serial.print(topic);
  Serial.print(" payload: ");
  Serial.println(msg);
 
  if(topic == (DHT_TOPIC1"/butt1"))
  {
    b1 = msg.toInt();
  }
  if(topic == (DHT_TOPIC2"/butt2"))
  {
    b2 = msg.toInt();
  }
  if(topic == (DHT_TOPIC3"/OutPir"))
  {
    OutPir = msg.toInt();
  }
}
 
// Function started after the connection to the server is established.
void iot_connected()
{
  Serial.println("MQTT connected callback");
  // Subscribe to the topic "pir"
  iot.subscribe(DHT_TOPIC1"/butt1");
  iot.subscribe(DHT_TOPIC2"/butt2");
  iot.subscribe(DHT_TOPIC2"/OutPir");
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

  myservo.attach(SERVO_PIN); // Setting the servo control pin
}
 
void loop()
{
  iot.handle(); // IoT behind the plan work, it should be periodically called
  delay(20); // Wait 0.02 seconds
  Serial.println("alive!");

  if (b1 && b2){
    full = true;
  }
  else {
    full = false;
  }
  
  // This part of the code is executed, when PIR shield is active
  if (OutPir){
    myservo.write(180);
  }
  else {
    if(digitalRead(PIR_PIN))
    {
      if(pirState == false)
      {
        // When PIR has detected motion, then servo is activated
        digitalWrite(PIR_LED_PIN, HIGH);
        String msg = String("1");
        iot.publishMsg("pir", msg.c_str());
        Serial.println(msg);
        if (!full){
          myservo.write(180);
        }
        pirState = true;
      }
    }
    else
    {
      if(pirState == true)
      {
        // When PIR has no motion, then servo is not activated
        digitalWrite(PIR_LED_PIN, LOW);
        String msg = String("0");
        iot.publishMsg("pir", msg.c_str());
        Serial.println(msg);
        myservo.write(0);
        pirState = false;
      }
    }
  }

    
}