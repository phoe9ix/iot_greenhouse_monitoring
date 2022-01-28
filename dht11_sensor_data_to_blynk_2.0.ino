/*
 * This program is property of SME Dehradun. for any query related to this program, contact us at www.smedehradn.com
 * if your want any soluiton related for any IoT Customized Boards and Sensor to www.nuttyengineer.com 
 */
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLLA7xUszQ"
#define BLYNK_DEVICE_NAME "Plant Monitoring Device"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"
#include "DHT.h"
#define DHTPIN D2 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float t, h;

void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature();  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  BlynkEdgent.begin();
  delay(2000); 
  timer.setInterval(1000L, sendSensor); 
}
int sensor=0;
int output=0;
void sendTemps()
{
sensor=analogRead(A0);
output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
delay(1000);
Blynk.virtualWrite(V2,output);
delay(1000);
}
void loop() 
{
  BlynkEdgent.run();
  sendTemps();
  timer.run(); // Initiates SimpleTimer
}
