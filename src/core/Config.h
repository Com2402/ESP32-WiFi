#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "Arduino.h"
#include "FileManager.h"
#include <ArduinoJson.h>
#include <WiFi.h> 
#include "WiFiManager.h"
#include <WiFiManager.h>
#include <EEPROM.h>
#include "esp_mac.h"
struct neworkItem
{
    String ssid;
    String password;
};
class Config
{
public:
    neworkItem ssids[5];
    Config() {}
    String defaultWifiConfig =  "{\"ID\":[{\"ssid\": \"WIFI1\",\"password\": \"24022002\"}, {\"ssid\": \"WIFI2\",\"password\": \"12345678\"}, {\"ssid\": \"WIFI3\",\"password\": \"12345678\"}, {\"ssid\": \"WIFI4\",\"password\": \"12345678\"}, {\"ssid\": \"WIFI5\",\"password\": \"12345678\"}]}";
    int index = 0;
    
public:
    
    void init();
    void addWifiConfig(String ssid, String password);
    void ConnectWiFi();

private:
    
    FileManager mFileManager;
    const char wifiConfigPath[24] = "/wifiConfig.json";
    WiFiManager wm; 
public:
    String readWiFiConfig();
    void writeWiFiConfig(const char *data);
    void checkWiFiConnect();
};

extern Config config;
#endif