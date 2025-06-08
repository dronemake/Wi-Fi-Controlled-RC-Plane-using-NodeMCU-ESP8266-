# Wi-Fi-Controlled-RC-Plane-using-NodeMCU-ESP8266-
This project allows you to control a mini RC plane wirelessly via a smartphone or browser using a custom-built web interface hosted on a NodeMCU (ESP8266) board. It uses Wi-Fi Access Point mode, so no external router or internet is needed.

## Features
🛩 Throttle & Turn Control via Web Interface
📶 Operates in Wi-Fi Access Point mode
🖥 Built-in Control Panel with responsive sliders
⚙️ Simple wiring and low power usage
🧠 Easily expandable for advanced flight features

## Components Used
NodeMCU ESP8266
Two brushed DC motors (left and right)
Motor driver or MOSFET circuit (as needed)
Power supply (LiPo battery or USB)
Optional: Onboard LED for connection status

## How to Use
Upload the code to your NodeMCU via Arduino IDE.
Power up the board.
Connect your phone/laptop to Wi-Fi SSID:
WIFI name : RC Plane
Password: 12345678

Open your browser and go to: http://192.168.4.1
Now
Use the Throttle (vertical) and Turn (horizontal) sliders to control the motors.
Throttle range: 0–255
Turn range: -100 (left) to +100 (right)
The turn slider auto-resets to 0 after each use for safe handling.

## Code Explanation
handleRoot(): Serves the main control panel (HTML/CSS/JS).
handleSet(): Receives throttle and turn values and sets motor speed accordingly.
analogWrite(): Controls motor PWM signals on pins D1 (GPIO5) and D2 (GPIO4).
WiFi.softAP(): Creates a local Wi-Fi hotspot without needing a router.

## Future Improvements
Add joystick-style controls for better flight feel.
Show real-time feedback (motor values or battery level).
Add extra channels (e.g. elevator, rudder).
Add safety features like throttle kill switch

## 📁 License
This project is open-source and free to use for educational and personal use.
Feel free to modify and improve it!
