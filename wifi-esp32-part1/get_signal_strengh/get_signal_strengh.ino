#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
SoftwareSerial mm (5, 4);


#define WIFI_SSID "Warmun18" 
#define WIFI_PASSWORD "dorayak1"

int sensor = A0;
int nilai;

WiFiClient client;
HTTPClient http;
ESP8266WiFiMulti WiFiMulti;


void setup(){
  Serial.println("Update");
  Serial.begin(9600);
  mm.begin(9600);
  connect_wifi();
}


void connect_wifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected");

}
void loop(){
  nilai = analogRead(sensor);
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(mm);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }
  String dht_temp = data["DHT22_TEMPERATURE"];
  String dht_hum = data["DHT22_HUMIDITY"];
  String raindrop = data["RAINDROP"];
  String soil = data["SOIL"];

  String output = "Potensiometer: "+String(nilai)+"|Temp : "+dht_temp+"|Humidity: "+dht_hum+"|Raindrop: "+raindrop+"|Soil : "+soil;

  Serial.println(output);
  upload(dht_temp, dht_hum, raindrop, String(nilai), soil);
  delay(1000);
  
}



void upload(String dht_temp, String dht_hum, String raindrop, String potensiometer, String soil){
  
  const char *url = "http://192.168.1.26:5000/humidity?id=add&value=222";
  /*
  String path_dht = url+"/humidity?id=add&value="+dht_hum;
  String path_raindrop = url+"/raindrop?id=add&value="+raindrop;
  String path_potensiometer = url+"/potensiometer?id=add&value="+potensiometer;
  String path_soil = url+"/soil?id=add&value="+soil;
  String path_temperature = url+"/temperature?id=add&value="+dht_temp;
  */

  Serial.println(url);
  if (WiFi.status()==WL_CONNECTED){

    if (http.begin(client,url)){
      int responsecode= http.GET();
      if (responsecode>0){
        Serial.println("[+] Success 200");
      }
      else{
        String payload = http.getString(); 
        
        Serial.println("[+] Failed -1");
        Serial.println(payload);
      }

    }
    else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  else{
    Serial.println("WiFi Disconnected");
  }
  delay(1000);


  /*
  http.begin(client, path_raindrop.c_str());
  http.begin(client, path_potensiometer.c_str());
  http.begin(client, path_soil.c_str());
  http.begin(client, path_temperature.c_str());
  */
  
}