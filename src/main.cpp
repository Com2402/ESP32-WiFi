#include "main.h"
#include <Arduino.h>
// #include <ArduinoJson>

// static const char *TAG = "[MAIN.CPP]";

void setup()
{
  // System init
  Serial.begin(115200);
  config.init();

  if (config.readWiFiConfig() == nullptr)
  {
    Serial.println("No WifiConfig file was found!");
    config.writeWiFiConfig(config.defaultWifiConfig.c_str());
    Serial.println("Default WifiCofnig file was created!");
  }
  else
  {
    Serial.println(config.readWiFiConfig());
    config.loadWifiConfig(config.defaultWifiConfig.c_str());
    
  }
  String ssid = WiFi.SSID(); 
  String password = WiFi.psk();
  config.addWifiConfig(ssid, password);
  Serial.println("New WiFi Config Saved:"); 
  config.ConnectWiFi();
  // Test data from user
  //   String data = "";
  //  config.writeWiFiConfig(data);
  //config.loadWifiConfig(config.defaultWifiConfig.c_str());
  
}
void loop()
{
}