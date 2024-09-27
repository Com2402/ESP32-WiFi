#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "Arduino.h"
#include "FileManager.h"
#include <ArduinoJson.h>
#include <WiFi.h> 
#include "WiFiManager.h"
#include <WiFiManager.h>
struct neworkItem
{
    String ssid;
    String password;
};

class Config
{
public:
    neworkItem ssids[5];
    String defaultWifiConfig = "{\"ID\":[{\"ssid\": \"WIFI\",\"password\": \"24022002\"}, {\"ssid\": \"2\",\"password\": \"12345678\"}, {\"ssid\": \"3\",\"password\": \"12345678\"}, {\"ssid\": \"4\",\"password\": \"12345678\"}, {\"ssid\": \"5\",\"password\": \"12345678\"}]}";
    int index = 0;
public:
    Config() {};
    void init();

private:
    
    FileManager mFileManager;
    const char wifiConfigPath[24] = "/config/wifiConfig.json";
    WiFiManager wm; 
public:
    String readWiFiConfig();
    void writeWiFiConfig(const char *data);
    void loadWifiConfig(const char *data);
    void ConnectWiFi();
    void addWifiConfig(String ssid, String password);
    
};

extern Config config;
#endif
