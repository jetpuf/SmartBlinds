/*
 *  Contains code from: 
 *  http://randomnerdtutorials.com/esp8266-remote-controlled-sockets/
 *  http://www.bruhautomation.com/p/cheapest-wifi-automated-blinds.html
 *  https://www.arduino.cc/en/Tutorial/Sweep
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#define WLAN_SSID       "YOUR WIFI SSID" //change to your Wifi SSID
#define WLAN_PASS       "YOUR WIFI PASSWORD" //change to your Wifi Password

MDNSResponder mdns;
ESP8266WebServer server(80);

int servoPin = 0; //Servo on GPIO0 or NODEMCU pin D3
const int buttonPin = 12; //manual button on GPIO12 or NODEMCU pin D6
int buttonState = 0;
int direction = 0;
int setting = 0; //Startup with blinds closed
int position = 90;
Servo servoA;

String webPage = "";

void setup(void) {
  WiFi.mode(WIFI_STA);
  webPage += "<h1>ESP8266 Web Server</h1><p>Blinds<br>";
  webPage += "<a href=\"0\"><button>0</button></a><br>";
  webPage += "<a href=\"10\"><button>10</button></a><br>";
  webPage += "<a href=\"20\"><button>20</button></a><br>";
  webPage += "<a href=\"30\"><button>30</button></a><br>";
  webPage += "<a href=\"40\"><button>40</button></a><br>";
  webPage += "<a href=\"50\"><button>50</button></a><br>";
  webPage += "<a href=\"60\"><button>60</button></a><br>";
  webPage += "<a href=\"70\"><button>70</button></a><br>";
  webPage += "<a href=\"80\"><button>80</button></a><br>";
  webPage += "<a href=\"90\"><button>90</button></a><br>";
  webPage += "<a href=\"100\"><button>100</button></a><br>";

  delay(1000);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  delay(500);
  Serial.println("Blind Startup Sequence");
  delay(500);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  // Set a static IP (optional)
  //IPAddress ip(10,0,1,50);
  //IPAddress gateway(10,0,1,1);
  //IPAddress subnet(255, 255, 255, 0);
  //WiFi.config(ip, gateway, subnet);
  // End of set a static IP (optional)
  delay(500);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    ESP.wdtFeed();
    if (i > 40)                                        // Try 40 times to connect to Wifi
      Serial.print("Restarting Wifi"); ESP.reset();    // Reset Wifi stack if more than 40 trys
    i++;
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    // Set a static IP retry (optional)
    //IPAddress ip(10,0,1,50);
    //IPAddress gateway(10,0,1,1);
    //IPAddress subnet(255, 255, 255, 0);
    //WiFi.config(ip, gateway, subnet);
    // End of set a static IP retry (optional)
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

server.on("/", []() { server.send(200, "text/html", webPage); });
server.on("/100", []() { server.send(200, "text/html", webPage); setting = 180; });
server.on("/99", []() { server.send(200, "text/html", webPage);  setting = 180; });
server.on("/98", []() { server.send(200, "text/html", webPage);  setting = 180; });
server.on("/97", []() { server.send(200, "text/html", webPage);  setting = 171; });
server.on("/96", []() { server.send(200, "text/html", webPage);  setting = 171; });
server.on("/95", []() { server.send(200, "text/html", webPage);  setting = 171; });
server.on("/94", []() { server.send(200, "text/html", webPage);  setting = 171; });
server.on("/93", []() { server.send(200, "text/html", webPage);  setting = 171; });
server.on("/92", []() { server.send(200, "text/html", webPage);  setting = 162; });
server.on("/91", []() { server.send(200, "text/html", webPage);  setting = 162; });
server.on("/90", []() { server.send(200, "text/html", webPage);  setting = 162; });

server.on("/89", []() { server.send(200, "text/html", webPage);  setting = 162; });
server.on("/88", []() { server.send(200, "text/html", webPage);  setting = 162; });
server.on("/87", []() { server.send(200, "text/html", webPage);  setting = 153; });
server.on("/86", []() { server.send(200, "text/html", webPage);  setting = 153; });
server.on("/85", []() { server.send(200, "text/html", webPage);  setting = 153; });
server.on("/84", []() { server.send(200, "text/html", webPage);  setting = 153; });
server.on("/83", []() { server.send(200, "text/html", webPage);  setting = 153; });
server.on("/82", []() { server.send(200, "text/html", webPage);  setting = 144; });
server.on("/81", []() { server.send(200, "text/html", webPage);  setting = 144; });
server.on("/80", []() { server.send(200, "text/html", webPage);  setting = 144; });

server.on("/79", []() { server.send(200, "text/html", webPage);  setting = 144; });
server.on("/78", []() { server.send(200, "text/html", webPage);  setting = 144; });
server.on("/77", []() { server.send(200, "text/html", webPage);  setting = 135; });
server.on("/76", []() { server.send(200, "text/html", webPage);  setting = 135; });
server.on("/75", []() { server.send(200, "text/html", webPage);  setting = 135; });
server.on("/74", []() { server.send(200, "text/html", webPage);  setting = 135; });
server.on("/73", []() { server.send(200, "text/html", webPage);  setting = 135; });
server.on("/72", []() { server.send(200, "text/html", webPage);  setting = 126; });
server.on("/71", []() { server.send(200, "text/html", webPage);  setting = 126; });
server.on("/70", []() { server.send(200, "text/html", webPage);  setting = 126; });

server.on("/69", []() { server.send(200, "text/html", webPage);  setting = 126; });
server.on("/68", []() { server.send(200, "text/html", webPage);  setting = 126; });
server.on("/67", []() { server.send(200, "text/html", webPage);  setting = 117; });
server.on("/66", []() { server.send(200, "text/html", webPage);  setting = 117; });
server.on("/65", []() { server.send(200, "text/html", webPage);  setting = 117; });
server.on("/64", []() { server.send(200, "text/html", webPage);  setting = 117; });
server.on("/63", []() { server.send(200, "text/html", webPage);  setting = 117; });
server.on("/62", []() { server.send(200, "text/html", webPage);  setting = 108; });
server.on("/61", []() { server.send(200, "text/html", webPage);  setting = 108; });
server.on("/60", []() { server.send(200, "text/html", webPage);  setting = 108; });

server.on("/59", []() { server.send(200, "text/html", webPage);  setting = 108; });
server.on("/58", []() { server.send(200, "text/html", webPage);  setting = 108; });
server.on("/57", []() { server.send(200, "text/html", webPage);  setting = 99; });
server.on("/56", []() { server.send(200, "text/html", webPage);  setting = 99; });
server.on("/55", []() { server.send(200, "text/html", webPage);  setting = 99; });
server.on("/54", []() { server.send(200, "text/html", webPage);  setting = 99; });
server.on("/53", []() { server.send(200, "text/html", webPage);  setting = 99; });
server.on("/52", []() { server.send(200, "text/html", webPage);  setting = 90; });
server.on("/51", []() { server.send(200, "text/html", webPage);  setting = 90; });
server.on("/50", []() { server.send(200, "text/html", webPage);  setting = 90; });

server.on("/49", []() { server.send(200, "text/html", webPage);  setting = 90; });
server.on("/48", []() { server.send(200, "text/html", webPage);  setting = 90; });
server.on("/47", []() { server.send(200, "text/html", webPage);  setting = 81; });
server.on("/46", []() { server.send(200, "text/html", webPage);  setting = 81; });
server.on("/45", []() { server.send(200, "text/html", webPage);  setting = 81; });
server.on("/44", []() { server.send(200, "text/html", webPage);  setting = 81; });
server.on("/43", []() { server.send(200, "text/html", webPage);  setting = 81; });
server.on("/42", []() { server.send(200, "text/html", webPage);  setting = 72; });
server.on("/41", []() { server.send(200, "text/html", webPage);  setting = 72; });
server.on("/40", []() { server.send(200, "text/html", webPage);  setting = 72; });


server.on("/39", []() { server.send(200, "text/html", webPage);  setting = 72; });
server.on("/38", []() { server.send(200, "text/html", webPage);  setting = 72; });
server.on("/37", []() { server.send(200, "text/html", webPage);  setting = 63; });
server.on("/36", []() { server.send(200, "text/html", webPage);  setting = 63; });
server.on("/35", []() { server.send(200, "text/html", webPage);  setting = 63; });
server.on("/34", []() { server.send(200, "text/html", webPage);  setting = 63; });
server.on("/33", []() { server.send(200, "text/html", webPage);  setting = 63; });
server.on("/32", []() { server.send(200, "text/html", webPage);  setting = 54; });
server.on("/31", []() { server.send(200, "text/html", webPage);  setting = 54; });
server.on("/30", []() { server.send(200, "text/html", webPage);  setting = 54; });

server.on("/29", []() { server.send(200, "text/html", webPage);  setting = 54; });
server.on("/28", []() { server.send(200, "text/html", webPage);  setting = 54; });
server.on("/27", []() { server.send(200, "text/html", webPage);  setting = 45; });
server.on("/26", []() { server.send(200, "text/html", webPage);  setting = 45; });
server.on("/25", []() { server.send(200, "text/html", webPage);  setting = 45; });
server.on("/24", []() { server.send(200, "text/html", webPage);  setting = 45; });
server.on("/23", []() { server.send(200, "text/html", webPage);  setting = 45; });
server.on("/22", []() { server.send(200, "text/html", webPage);  setting = 36; });
server.on("/21", []() { server.send(200, "text/html", webPage);  setting = 36; });
server.on("/20", []() { server.send(200, "text/html", webPage);  setting = 36; });

server.on("/19", []() { server.send(200, "text/html", webPage);  setting = 36; });
server.on("/18", []() { server.send(200, "text/html", webPage);  setting = 36; });
server.on("/17", []() { server.send(200, "text/html", webPage);  setting = 27; });
server.on("/16", []() { server.send(200, "text/html", webPage);  setting = 27; });
server.on("/15", []() { server.send(200, "text/html", webPage);  setting = 27; });
server.on("/14", []() { server.send(200, "text/html", webPage);  setting = 27; });
server.on("/13", []() { server.send(200, "text/html", webPage);  setting = 27; });
server.on("/12", []() { server.send(200, "text/html", webPage);  setting = 18; });
server.on("/11", []() { server.send(200, "text/html", webPage);  setting = 18; });
server.on("/10", []() { server.send(200, "text/html", webPage);  setting = 18; });  

server.on("/9", []() { server.send(200, "text/html", webPage);   setting = 18; });
server.on("/8", []() { server.send(200, "text/html", webPage);   setting = 18; });
server.on("/7", []() { server.send(200, "text/html", webPage);   setting = 9; });
server.on("/6", []() { server.send(200, "text/html", webPage);   setting = 9; });
server.on("/5", []() { server.send(200, "text/html", webPage);   setting = 9; });
server.on("/4", []() { server.send(200, "text/html", webPage);   setting = 9; });
server.on("/3", []() { server.send(200, "text/html", webPage);   setting = 9; });
server.on("/2", []() { server.send(200, "text/html", webPage);   setting = 0; });
server.on("/1", []() { server.send(200, "text/html", webPage);   setting = 0; });
server.on("/0", []() { server.send(200, "text/html", webPage);   setting = 0; });
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
buttonState = digitalRead(buttonPin);

if(buttonState == LOW && setting <= 180 && direction == 0){
  setting++;
  delay(0);
  if(setting == 180){
    direction = 1;
    }
  }
  
if(buttonState == LOW && setting >= 0 && direction == 1){
  setting--;
  delay(0);
  if(setting == 0){
    direction = 0;
    }
  }

if(position < setting){
   servoA.attach(servoPin);
   servoA.write(position++);
   delay(5);
     Serial.print("Setting: ");  
     Serial.println(setting);
     Serial.print("Position: ");
     Serial.println(position);
   }
   
if(position > setting){
   servoA.attach(servoPin);
   servoA.write(position--);
   delay(5);
     Serial.print("Setting: ");  
     Serial.println(setting);
     Serial.print("Position: ");
     Serial.println(position);
   }

if(position == setting){
  servoA.detach();
  }
server.handleClient();
}
