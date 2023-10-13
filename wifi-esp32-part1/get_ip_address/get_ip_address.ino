#include <WiFi.h>

const char* ssid = "myskill";
const char* password = "myskill123";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println(WiFi.localIP());
}