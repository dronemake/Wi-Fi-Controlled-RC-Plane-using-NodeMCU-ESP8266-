#include <ESP8266WiFi.h>               // Libraries Used to set up the ESP8266 as a Wi-Fi access point.
#include <ESP8266WebServer.h>          // Libraries Used to Allows serving a simple web page and handling HTTP requests.

#define ST_LED  2       // On-board status LED
#define L_MOTOR 5        // Left motor (D1)
#define R_MOTOR 4        // Right motor (D2)

const char* ssid = "RCplane0";       // ESP8266 will act as a Wi-Fi Access Point with this SSID and password.
const char* password = "RCplane0";

ESP8266WebServer server(80);         // Sets up an HTTP web server on port 80 (default)

//Global Control Variables

unsigned int throttle = 0; // Controls motor speed (0–255 range).
int turn = 0;              // Controls direction (-100 to +100 range).

// Web Interface Page

void handleRoot() { 
  String page = "<!DOCTYPE html><html><head><title>RC Plane Control</title>";   // Starts the HTML page with a title.
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<style>body { font-family: Arial; text-align: center; }"; // adds basic style for the page (centering content, fonts, containers).
  page += "#throttle-container { width: 50px; height: 200px; background: lightgray; margin: 20px auto; position: relative; border-radius: 10px; }";
  //  Throttle slider container (vertical):
  page += "#throttle { width: 100%; height: 100%; writing-mode: bt-lr; -webkit-appearance: slider-vertical; }"; 
  //  Turn slider container (horizontal):
  page += "#turn-container { width: 200px; height: 50px; background: lightgray; margin: 20px auto; position: relative; border-radius: 10px; }";
  page += "#turn { width: 100%; height: 100%; -webkit-appearance: slider-horizontal; }"; 
  page += "</style></head><body>";
  page += "<h2>Wifi Control RC Plane </h2>";

// Throttle (vertical range slider from 0 to 255).
  page += "<label>Throttle</label><div id='throttle-container'><input type='range' min='0' max='255' value='0' id='throttle' orient='vertical' oninput='updateControl()'></div><br>";
// Turn (horizontal slider from -100 to +100).
  page += "<label>Turn</label><div id='turn-container'><input type='range' min='-100' max='100' value='0' id='turn' oninput='updateControl()' onmouseup='resetTurn()' ontouchend='resetTurn()'></div>";  // Calls JavaScript function when slider moves.
// Uses JavaScript to send values to the server using fetch().
// When a user changes the slider, this sends throttle and turn values to the server via /set URL.


// JavaScript Functions – Live Control
  page += "<script>function updateControl() { fetch(`/set?t=${document.getElementById('throttle').value}&tr=${document.getElementById('turn').value}`); }";
  page += "function resetTurn() { document.getElementById('turn').value = 0; updateControl(); }</script></body></html>";
  server.send(200, "text/html", page);
}

void handleSet() {    // //  Handling Slider Values
  if (server.hasArg("t")) throttle = server.arg("t").toInt();  // Reads the t (throttle) and tr (turn) values from the URL.
  if (server.hasArg("tr")) turn = server.arg("tr").toInt();

  // Calculates individual motor speeds:
  unsigned int l_speed = constrain(throttle + turn, 0, 255); // Uses constrain() to limit values between 0–90 (this is important to protect the motors)
  unsigned int r_speed = constrain(throttle - turn, 0, 255);
  
  // // Sends PWM signals to the left and right motors using analogWrite.
  analogWrite(L_MOTOR, l_speed); 
  analogWrite(R_MOTOR, r_speed);
  server.send(200, "text/plain", "OK");


}

void setup() {   // Setup Function for motor pins and LED as outputs.
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);
  pinMode(ST_LED, OUTPUT);
  analogWrite(L_MOTOR, 0);
  analogWrite(R_MOTOR, 0);



// Start WiFi in AP mode 
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.begin(115200);
  Serial.print("AP IP address: ");
  Serial.println(IP);

// Starts the web server and attaches handlers for / and /set.
  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

// Main Loop for Continuously checks and processes HTTP requests.
void loop() {
  server.handleClient();

}
