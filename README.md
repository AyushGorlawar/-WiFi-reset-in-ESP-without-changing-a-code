# WiFi-reset-in-ESP-without-changing-a-code



## Overview
This project sets up an ESP8266 web server that allows users to:
- View the device's IP address and connected WiFi network.
- Refresh weather data (future feature integration required).
- Reset WiFi credentials and reconnect via WiFiManager.

## Features
- **WiFi Manager**: Automatically connects to saved WiFi or creates an Access Point (`ESP-Weather-Setup`) for user configuration.
- **Web Server**: Hosts a simple webpage to display device information and control WiFi settings.
- **Auto Refresh**: Implements JavaScript-based auto-refresh for weather data (weather API integration needed).
- **Reset WiFi Settings**: Users can reset WiFi credentials, forcing a new setup.

## Requirements
- **Hardware**: ESP8266-based board (e.g., NodeMCU, Wemos D1 Mini)
- **Software**:
  - Arduino IDE with ESP8266 board support
  - Libraries:
    - `ESP8266WiFi`
    - `ESP8266WebServer`
    - `ESP8266HTTPClient`
    - `ArduinoJson`
    - `WiFiManager`

## Installation & Setup
1. **Install Required Libraries**: Use Arduino Library Manager to install the dependencies listed above.
2. **Upload the Code**: Flash the provided ESP8266 script to your board using Arduino IDE.
3. **Connect to WiFi**:
   - If no WiFi is configured, connect to the `ESP-Weather-Setup` access point.
   - Open a browser and visit `192.168.4.1` to enter WiFi credentials.
   - Once connected, note the assigned IP address in the Serial Monitor.
4. **Access the Web Interface**:
   - Open a browser and enter the ESP8266's local IP address.
   - Use the web interface to view details and reset WiFi if needed.

## API Endpoints
| Endpoint       | Method | Description |
|---------------|--------|-------------|
| `/`           | GET    | Main page with device info & controls |
| `/refresh`    | GET    | Refreshes weather data (to be implemented) |
| `/resetWiFi`  | GET    | Resets WiFi settings and restarts ESP |
| `/style.css`  | GET    | Serves the webpage CSS styling |

## Future Enhancements
- **Weather API Integration**: Fetch and display real-time weather data.
- **Temperature & Sensor Support**: Connect sensors like DHT11/DHT22 for local weather readings.
- **OTA Updates**: Implement over-the-air firmware updates.

## License
This project is open-source and free to use under the Apache License 2.0.

---
### 📌 Note:
Ensure you have a stable power source for ESP8266 to avoid unexpected reboots.

