#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int AirValue = 50;   //replace the value from calibration in air
const int WaterValue = 0;  //replace the value from calibration in water
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
BlynkTimer timer;
char auth[] = "Jdr6OZuoUSK-S-Fvr6tW-2M4N3HHLpEn";              //Authentication code sent by Blynk
char ssid[] = "--------------------------";                    //WiFi SSID
char pass[] = "--------------------------";                    //WiFi Password
void MainFunction() {
  soilMoistureValue = analogRead(A0); //Mention where the analog pin is connected on NodeMCU
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent < 10) // change this at what level the pump turns on
  {
    Serial.println("Nearly dry, Pump turning on");
    digitalWrite(D5, HIGH); // Low percent high signal to relay to turn on pump
  }
  else if (soilmoisturepercent > 85) // max water level should be
  {
    Serial.println("Nearly wet, Pump turning off");
    digitalWrite(D5, LOW); // high percent water high signal to relay to turn off pump
  }
  Blynk.virtualWrite(V2, soilmoisturepercent); //display the moisture percent.
}

void setup() {
  pinMode(D5, OUTPUT); // pin where relay trigger connected
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  Blynk.begin(auth,ssid,pass);
  timer.setInterval(1000L, MainFunction);

}
void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
