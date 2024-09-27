#include "Config.h"

Config config;

void Config::init()
{
    
    mFileManager.init();
}

String Config::readWiFiConfig()
{
    return mFileManager.readFile(SPIFFS, wifiConfigPath);
}


void Config::writeWiFiConfig(const char *data)
{
    mFileManager.writeFile(SPIFFS, wifiConfigPath, data);
}

void Config::loadWifiConfig(const char *data)
{
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, data);
  JsonArray wifiArray = doc["ID"];
  
  int i = 0;
  for (JsonObject wifidoc : wifiArray) {
    ssids[i].ssid = wifidoc["ssid"].as<String>();
    ssids[i].password = wifidoc["password"].as<String>();
    
    Serial.print("SSID: ");
    Serial.println(ssids[i].ssid);
    Serial.print("Password: ");
    Serial.println(ssids[i].password);
    i++;
    if (i > 4) break; 
  }

}
void Config::addWifiConfig(String ssid, String password) {
    if (index < 5) {
        ssids[index].ssid = ssid;
        ssids[index].password = password;
        index++; 
    } else {
        
        for (int i = 1; i < 5; i++) {
            ssids[i - 1] = ssids[i]; 
        }
        ssids[4].ssid = ssid; 
        ssids[4].password = password;
    }

    
    String newConfig = "{\"ID\":[";
    for (int j = 0; j < index; j++) {
        newConfig += "{\"ssid\": \"" + ssids[j].ssid + "\", \"password\": \"" + ssids[j].password + "\"}";
        if (j < index - 1) newConfig += ",";
    }
    newConfig += "]}";
    writeWiFiConfig(newConfig.c_str()); 
}
void Config::ConnectWiFi(){
    for(int i = 0; i < index ;i++){
        WiFi.begin(ssids[i].ssid.c_str(), ssids[i].password.c_str());
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 3) {
            delay(500);
            Serial.print(".");
            attempts++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println();
            Serial.print("Connected to WiFi: ");
            Serial.println(ssids[i].ssid);
            return; 
        } else {
            Serial.println();
            Serial.print("Failed to connect");

        }
    
    }
    wm.autoConnect("ConnectAP");
    String ssid = WiFi.SSID(); 
    String password = WiFi.psk();
    config.addWifiConfig(ssid, password);
    Serial.println("New WiFi Config Saved:"); 
   
}
