#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

// Server setup
ESP8266WebServer server(80);

void handleWiFiReset();
void handleRoot();
void handleRefresh();
void handleCSS();

void setup() {
  Serial.begin(115200);
  
  // WiFiManager - handles connecting to WiFi
  WiFiManager wifiManager;
  
  // Uncomment to reset saved settings
  // wifiManager.resetSettings();
  
  // Creates an access point named "ESP-AP-Setup" if it can't connect to saved WiFi
  if (!wifiManager.autoConnect("ESP-AP-Setup")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Server Routes
  server.on("/resetWiFi", handleWiFiReset);
  server.on("/", handleRoot);
  server.on("/refresh", handleRefresh);
  server.on("/style.css", handleCSS);
  
  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleWiFiReset() {
  server.send(200, "text/html", 
    "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "<title>Resetting WiFi...</title>"
    "<style>body{font-family:Arial,sans-serif;text-align:center;padding:20px;}</style>"
    "</head><body>"
    "<h2>WiFi Settings Reset</h2>"
    "<p>WiFi credentials have been reset. The device will restart and create an access point named 'ESP-Weather-Setup'.</p>"
    "<p>Connect to this network to configure new WiFi settings.</p>"
    "</body></html>");

  delay(2000);

  WiFiManager wifiManager;
  wifiManager.resetSettings();
  ESP.restart();
}

void handleRoot() {
  String html = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                "<title>ESP8266 AP CONFIG</title>"
                "<link rel='stylesheet' type='text/css' href='/style.css'>"
                "<script>"
                "function refreshWeather() {"
                "  fetch('/weather')"
                "    .then(response => response.json())"
                "    .then(data => {"
                "      setInterval(refreshWeather, 10000);"
                "    });"
                "}"
                "document.addEventListener('DOMContentLoaded', refreshWeather);"
                "</script>"
                "</head>"
                "<body>"
                "<div class='device-info'>"
                "<div>Device IP: " + WiFi.localIP().toString() + "</div>"
                "<div>WiFi: " + String(WiFi.SSID()) + "</div>"
                "</div>"
                "<div class='last-update' id='last-update'>Last updated: --</div>"
                "<button onclick='refreshWeather()'>Refresh Now</button>"
                "<div class='wifi-reset'>"
                "<hr>"
                "<h3>WiFi Settings</h3>"
                "<p class='warning'>Warning: Clicking the button below will reset your WiFi settings and restart the device.</p>"
                "<button class='danger-btn' onclick=\"if(confirm('Are you sure you want to reset WiFi settings? This will restart the device.')) { window.location.href='/resetWiFi'; }\">Reset WiFi Settings</button>"
                "</div>"
                "</body>"
                "</html>";
  server.send(200, "text/html", html);
}

void handleRefresh() {
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleCSS() {
  String css = "body { font-family: Arial, sans-serif; background-color: #f5f5f5; color: #333; }"
               "button { padding: 10px 20px; background-color: #0066cc; color: white; border: none; border-radius: 5px; cursor: pointer; font-size: 1em; }"
               "button:hover { background-color: #0055aa; }"
               ".wifi-reset { background-color: #fff0f0; padding: 15px; border-radius: 8px; }"
               ".warning { color: #cc0000; font-size: 0.9em; margin-bottom: 10px; }"
               ".danger-btn { background-color: #cc0000; margin-top: 10px; }"
               ".danger-btn:hover { background-color: #aa0000; }";
  server.send(200, "text/css", css);
}
