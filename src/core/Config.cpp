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
void Config::addWifiConfig(String ssid, String password) {
    String wifiConfig = readWiFiConfig(); 
    DynamicJsonDocument doc(1024);   
    DeserializationError error = deserializeJson(doc, wifiConfig);

    JsonArray networks = doc["ID"].as<JsonArray>();

    JsonObject newWifi = networks.add<JsonObject>();
    newWifi["ssid"] = ssid;
    newWifi["password"] = password;
    if (networks.size() > 5) {
        networks.remove(0);
    }
    String updatedConfig;
    serializeJson(doc, updatedConfig);
    writeWiFiConfig(updatedConfig.c_str());

    Serial.println("Updated WiFi Config:");
    Serial.println(updatedConfig);
}
void Config::ConnectWiFi() {
    WiFiManager wm;

    
    String wifiConfig = readWiFiConfig();
    
    if (wifiConfig.length() > 0) {
      
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, wifiConfig);
        
        if (!error && doc.containsKey("ID")) {
            JsonArray networks = doc["ID"];
            for (JsonObject wifi : networks) {
                String ssid = wifi["ssid"].as<String>();
                String password = wifi["password"].as<String>();

                Serial.printf("Connect to %s\n", ssid.c_str());
                
                WiFi.begin(ssid.c_str(), password.c_str());
                int attempts = 0;
                while (WiFi.status() != WL_CONNECTED && attempts < 10) {
                    delay(500);
                    Serial.print(".");
                    attempts++;
                }
                
                if (WiFi.status() == WL_CONNECTED) {
                    Serial.printf("\nConnected to %s\n", ssid.c_str());
                    return;
                } else {
                    Serial.printf("\nFailed to connect to %s\n", ssid.c_str());
                }
            }
        }
    }

    Serial.println("Starting AP mode");
    wm.setConfigPortalTimeout(180);
    if (wm.autoConnect("ESP_AP")) {
        Serial.println("Connected to WiFi via Config Portal");
        String newSsid = WiFi.SSID();
        String newPassword = WiFi.psk();
        addWifiConfig(newSsid, newPassword);
        Serial.println("Updated WiFi configurations:");
        Serial.println(readWiFiConfig());
    } else {
        Serial.println("Failed to connect and hit timeout");
        ESP.restart();
    }
}
void Config::checkWiFiConnect(){
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection lost, starting AP mode");
      
        WiFiManager wm;
       if (wm.autoConnect("ESP_AP")) {
        Serial.println("Connected to WiFi via Config Portal");
        String newSsid = WiFi.SSID();
        String newPassword = WiFi.psk();
        addWifiConfig(newSsid, newPassword);
    } else {
        Serial.println("Failed to connect and hit timeout");
        ESP.restart();
    }
    }
}






// void Config::ConnectWiFi() {
//     WiFiManager wm;

//     // Đọc cấu hình WiFi từ SPIFFS
//     String wifiConfig = readWiFiConfig();
    
//     if (wifiConfig.length() > 0) {
//         // Parse JSON
//         DynamicJsonDocument doc(1024);
//         DeserializationError error = deserializeJson(doc, wifiConfig);
        
//         if (!error && doc.containsKey("ID")) {
//             JsonArray networks = doc["ID"];
//             // Thử kết nối với từng mạng WiFi đã lưu
//             for (JsonObject wifi : networks) {
//                 String ssid = wifi["ssid"].as<String>();
//                 String password = wifi["password"].as<String>();

//                 Serial.printf("Attempting to connect to %s\n", ssid.c_str());
                
//                 WiFi.begin(ssid.c_str(), password.c_str());
//                 int attempts = 0;
//                 while (WiFi.status() != WL_CONNECTED && attempts < 20) {
//                     delay(500);
//                     Serial.print(".");
//                     attempts++;
//                 }
                
//                 if (WiFi.status() == WL_CONNECTED) {
//                     Serial.printf("\nConnected to %s\n", ssid.c_str());
//                     return;
//                 } else {
//                     Serial.printf("\nFailed to connect to %s\n", ssid.c_str());
//                 }
//             }
//         }
//     }

//     // Nếu không thể kết nối với bất kỳ mạng nào đã lưu
//     Serial.println("Starting AP mode");
    
//     // Cấu hình cho AP
//     wm.setConfigPortalTimeout(180); // 3 minutes timeout

//     if (wm.startConfigPortal("ESP_AP")) {
//         Serial.println("Connected to WiFi via Config Portal");
//         String newSsid = WiFi.SSID();
//         String newPassword = WiFi.psk();
        
//         // Thêm cấu hình WiFi mới (sẽ tự động xử lý FIFO trong addWifiConfig)
//         addWifiConfig(newSsid, newPassword);
        
//         Serial.println("Updated WiFi configurations:");
//         Serial.println(readWiFiConfig());
//     } else {
//         Serial.println("Failed to connect and hit timeout");
//         ESP.restart();
//     }
// }