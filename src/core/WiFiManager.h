#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__
#include <WiFi.h>
#include <Arduino_JSON.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "ArduinoJson.h"
#include <DNSServer.h>
#include <Preferences.h>
#include <esp32-hal-log.h>
#include "Config.h"

#ifdef DEBUG_LOG
bool _debug = true;
#endif
#ifndef WIFIMANAGER_MAX_APS
#define WIFIMANAGER_MAX_APS 5 // Valid range is uint8_t
#endif

extern TaskHandle_t WifiCheckTask;

const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>

)rawliteral";

String processorWiFiManager(const String &var);
// function handle when user get unknow router
extern void notFound(AsyncWebServerRequest *request);
class WiFiManager
{
public:
  bool status = false; // variable use to active wifmanager
  unsigned long previousMillis_cnWifi = 0;
  unsigned int count_retry_connect = 0;
  const char passAP[11] = "vietqr.com";
  const char NVS[18] = "WiFiStorage";

  typedef struct apCredentials_t
  {
    String apName; // Name of the AP SSID
    String apPass; // Password if required to the AP
  } WifiAPlist_t;

  apCredentials_t apList[WIFIMANAGER_MAX_APS];

  uint8_t configuredSSIDs = 0; // Number of stored SSIDs in the NVS

  bool softApRunning = false;   // Due to lack of functions, we have to remember if the AP is already running...
  bool createFallbackAP = true; // Create an AP for configuration if no other connection is ava

  uint64_t lastWifiCheckMillis = 0;         // Time of last Wifi health check
  uint32_t intervalWifiCheckMillis = 15000; // Interval of the Wifi health checks
  uint64_t startApTimeMillis = 0;           // Time when the AP was started
  uint32_t timeoutApMillis = 120000;        // Timeout of an AP when no client is connected, if timeout reached rescan, tryconnect or createAP

  // Wipe the apList credentials
  void clearApList();

  // Get id of the first non empty entry
  uint8_t getApEntry();

public:
  WiFiManager();
  ~WiFiManager();
  void removeApList();
  // If no known Wifi can't be found, create an AP but retry regulary
  void fallbackToSoftAp(bool state = true);

  // Add another AP to the list of known WIFIs
  bool addWifi(String apName, String apPass, bool updateNVS = true, bool fromAP = false);

  // Delete Wifi from apList by ID
  bool delWifi(uint8_t apId);

  // Delete Wifi from apList by Name
  bool delWifi(String apName);

  // Check if a SSID is stored in the config
  bool configAvailable();

  // Write AP Settings into persistent storage. Called on each addAP;
  bool writeToNVS();

  // Load AP Settings from NVS it known apList
  bool loadFromNVS();

  // Try each known SSID and connect until none is left or one is connected.
  bool connectWiFi();

  String getIPAddress();
  String getSSID();
  int8_t getRSSI();
  void startAP(String ssidAP = "");
  void autoReconnectWiFi();

  class CaptiveRequestHandler : public AsyncWebHandler
  {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}
    bool canHandle(AsyncWebServerRequest *request)
    {
      request->addInterestingHeader("ANY");
      return true;
    }
    void handleRequest(AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", index_html, processorWiFiManager);
    }
  };
  // AsyncCallbackJsonWebHandler *handlerJson = nullptr;

private:
  String ssid;
  String pass;
  String ip;
  String gateway;
  bool useStaticIP;
  int8_t rssi;
  const byte DNS_PORT = 53;

  Preferences preferences; // Used to store AP credentials to NVS
};

// export variable
extern AsyncWebServer &getInstanceAsyncWebserver();
extern WiFiManager &getInstanceWF();
#endif