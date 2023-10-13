#include <WiFi.h>

const char* ssid = "myskill";
const char* password = "password123";

void setup() {
  Serial.begin(115200);

  // Set WiFi mode to Access Point
  WiFi.mode(WIFI_AP);

  // Start Access Point
  WiFi.softAP(ssid, password);
  
  Serial.println("Access Point started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Do nothing in the loop
}
