// 365_WeMos_D1_mini_RGB_shield_wifi
// WeMos_D1_mini
// WS2812B RGB shield HV-705
// WiFi

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
 
const char* ssid = "**********";
const char* password = "*********";
const int PIN      = D2;           // WS2812B RGB shield HV-705

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
  pixels.begin(); // This initializes the NeoPixel library.
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 

  if (request.indexOf("/RED=ON") != -1) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red
    pixels.show();                                    // This sends the updated pixel color to the hardware. 
  } 

  if (request.indexOf("/GREEN=ON") != -1) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Green
    pixels.show(); 
  } 
  
 if (request.indexOf("/BLUE=ON") != -1) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Blue
    pixels.show(); 
  } 
  
  if (request.indexOf("/ALL=OFF") != -1){  
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Nothing
    pixels.show();                                   
   
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  
  client.println("<html>"); 
  client.println("<br><br>"); 
  client.println("Click <a href=\"/RED=ON\">here</a> turn the RED LED ON<br>");
  client.println("<br><br>");
  client.println("******************************************<br>");
  client.println("<br><br>");
  client.println("Click <a href=\"/GREEN=ON\">here</a> turn the GREEN LED ON<br>");
  client.println("<br><br>");
  client.println("******************************************<br>");
  client.println("<br><br>"); 
  client.println("Click <a href=\"/BLUE=ON\">here</a> turn the BLUE LED ON<br>");
  client.println("<br><br>");
  client.println("******************************************<br>");
  client.println("<br><br>");
  client.println("Click <a href=\"/ALL=OFF\">here</a> turn the ALL LED OFF<br>");
  client.println("<br><br>");
  client.println("******************************************<br>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disconnected");
  Serial.println(""); 
}
/*    
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));      // Red    
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));      // Green
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));      // Blue  
      pixels.setPixelColor(0, pixels.Color(210,31,60));      // Raspberry     //vzor (255, 255, 125)   
      pixels.setPixelColor(0, pixels.Color(0, 255, 255));    // Cyan 
      pixels.setPixelColor(0, pixels.Color(255, 0, 255));    // Magenta
      pixels.setPixelColor(0, pixels.Color(255, 255, 0));     // Yellow   
      pixels.setPixelColor(0, pixels.Color(255, 255, 255));   // White
*/
