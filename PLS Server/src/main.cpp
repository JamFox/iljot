// Includes global variables and librarys that the OLED display uses
#include <Arduino.h>
#include <ittiot.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WEMOS_Matrix_GFX.h>

#define WIFI_NAME "11T Pro"
#define WIFI_PASSWORD "Io376256"


// Change it according to the real name of the microcontroller where DHT shield is connected
#define DHT_TOPIC1 "ESP32"
#define DHT_TOPIC2 "ESP05"
#define DHT_TOPIC3 "ESP36"
 
// OLED reset pin is GPIO0
#define OLED_RESET 0
 
// Create an object for OLED screen
Adafruit_SSD1306 display(OLED_RESET);
 
// Define variables to store data
boolean h;
boolean b1;
boolean b2;

MLED matrix(7); //set intensity=7 (maximum)
 
// Message received
void iot_received(String topic, String msg)
{
  // Check for motion data
  if(topic == (DHT_TOPIC1"/pir"))
  {
    h = msg.toInt(); // Convert string to float
  }
  // Check for parking spot 1 data
  if(topic == (DHT_TOPIC2"/butt1"))
  {
    b1 = msg.toInt(); // Convert string to float
  }
  // Check for parking spot 2 data
  if(topic == (DHT_TOPIC2"/butt2"))
  {
    b2 = msg.toInt(); // Convert string to float
  }
}
 
// Function started after the connection to the server is established.
void iot_connected()
{
  // Send message to serial port to show that connection is established
  Serial.println("MQTT connected callback");
  // Subscribe to topics for messages
  iot.subscribe(DHT_TOPIC2"/butt1");
  iot.subscribe(DHT_TOPIC3"/butt2");
  iot.subscribe(DHT_TOPIC1"/pir");
  // Send message to MQTT server to show that connection is established
  iot.log("IoT OLED example!");
}
 
void setup()
{
  // Initialize serial port and send message
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");
 
  // Initialize OLED with the I2C addr 0x3C (for the 64x48)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // Display "booting..." message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Booting...");
  display.display();
 
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.printConfig(); // print IoT json config to serial
  iot.setup(); // Initialize IoT library
}
 
void loop()
{
  iot.handle();// IoT behind the plan work, it should be periodically called
 
  display.clearDisplay(); // cleanse the OLED display
  display.setTextSize(1); // sets the text size
  display.setTextColor(WHITE); // sets the text color
  display.setCursor(0,0); // sets the cursor position
  display.print(b2);
  display.setCursor(0,20);
  display.display();


  if (b1) { // If button on parking lot is pressed - led is on
    matrix.clear(); // Clear the matrix field
    matrix.drawPixel(3,4, LED_ON);
    matrix.writeDisplay();  // Write the changes we just made to the display
  } else { // led is off
    matrix.clear(); // Clear the matrix field
    matrix.drawPixel(3,4, LED_OFF);
    matrix.writeDisplay();  // Write the changes we just made to the display
  }

  if (b2) { // If button on parking lot is pressed - led is on
    matrix.clear(); // Clear the matrix field
    matrix.drawPixel(4,4, LED_ON);
    matrix.writeDisplay();  // Write the changes we just made to the display
  } else { // led is off
    matrix.clear(); // Clear the matrix field
    matrix.drawPixel(4,4, LED_OFF);
    matrix.writeDisplay();  // Write the changes we just made to the display
  }
 
  delay(1); // Waiting 0.01 second
}