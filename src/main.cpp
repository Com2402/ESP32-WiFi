#include "main.h"
#include <Arduino.h>
#include "Config.h"
#include <WiFiManager.h>

void setup()
{
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
}
  
  Serial.begin(115200);
  config.init();
  //config.writeWiFiConfig(config.defaultWifiConfig.c_str());
  // if (config.readWiFiConfig() == nullptr)
  // {
  //   Serial.println("No WifiConfig file was found!");

  //   config.writeWiFiConfig(config.defaultWifiConfig.c_str());
  //   Serial.println("Default WifiCofnig file was created!");
  // }
  // else
  // {
  //   Serial.println(config.readWiFiConfig());
  // }
 config.ConnectWiFi();
}
void loop()
{
    config.checkWiFiConnect();

}






















































