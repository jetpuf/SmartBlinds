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
#include <ESP8266WifiMulti.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <Servo.h>
#include <EEPROM.h>

#define WLAN_SSID       "YOUR WIFI SSID" //change to your Wifi SSID
#define WLAN_PASS       "YOUR WIFI PASSWORD" //change to your Wifi Password
int servoPin = 2; //Servo on GPIO2 or D4 on Wemos D1 Mini

ESP8266WiFiMulti WiFiMulti;
ESP8266WebServer server(80);
int WriteState = 0; //Write EEPROM when value 1
String webPage = "";
Servo servoA;
int Setting = 0;
int Position = 0;
void setup(void) {
  
  servoA.attach(servoPin);
  EEPROM.begin(4);
  Setting = EEPROM.read(0); //read from eeprom value 0
  Position = EEPROM.read(1); //read from eeprom value 1
  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
  
  Serial.begin(9600);
  delay(500);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WLAN_SSID, WLAN_PASS);
  Serial.println();
  Serial.print("Wait for WiFi...");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  delay(500);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Setting: ");
  Serial.println(EEPROM.read(0));
  Serial.print("Position: ");
  Serial.println(EEPROM.read(1));

//Webpage
  webPage += "<h1>Wifi Window Blinds</h1><br>";
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

//Settings from SmartThings web calls
server.on("/", []() { server.send(200, "text/html", webPage); });
server.on("/100", []() { server.send(200, "text/html", webPage); Setting = 180; });
server.on("/99", []() { server.send(200, "text/html", webPage);  Setting = 180; });
server.on("/98", []() { server.send(200, "text/html", webPage);  Setting = 180; });
server.on("/97", []() { server.send(200, "text/html", webPage);  Setting = 171; });
server.on("/96", []() { server.send(200, "text/html", webPage);  Setting = 171; });
server.on("/95", []() { server.send(200, "text/html", webPage);  Setting = 171; });
server.on("/94", []() { server.send(200, "text/html", webPage);  Setting = 171; });
server.on("/93", []() { server.send(200, "text/html", webPage);  Setting = 171; });
server.on("/92", []() { server.send(200, "text/html", webPage);  Setting = 162; });
server.on("/91", []() { server.send(200, "text/html", webPage);  Setting = 162; });
server.on("/90", []() { server.send(200, "text/html", webPage);  Setting = 162; });

server.on("/89", []() { server.send(200, "text/html", webPage);  Setting = 162; });
server.on("/88", []() { server.send(200, "text/html", webPage);  Setting = 162; });
server.on("/87", []() { server.send(200, "text/html", webPage);  Setting = 153; });
server.on("/86", []() { server.send(200, "text/html", webPage);  Setting = 153; });
server.on("/85", []() { server.send(200, "text/html", webPage);  Setting = 153; });
server.on("/84", []() { server.send(200, "text/html", webPage);  Setting = 153; });
server.on("/83", []() { server.send(200, "text/html", webPage);  Setting = 153; });
server.on("/82", []() { server.send(200, "text/html", webPage);  Setting = 144; });
server.on("/81", []() { server.send(200, "text/html", webPage);  Setting = 144; });
server.on("/80", []() { server.send(200, "text/html", webPage);  Setting = 144; });

server.on("/79", []() { server.send(200, "text/html", webPage);  Setting = 144; });
server.on("/78", []() { server.send(200, "text/html", webPage);  Setting = 144; });
server.on("/77", []() { server.send(200, "text/html", webPage);  Setting = 135; });
server.on("/76", []() { server.send(200, "text/html", webPage);  Setting = 135; });
server.on("/75", []() { server.send(200, "text/html", webPage);  Setting = 135; });
server.on("/74", []() { server.send(200, "text/html", webPage);  Setting = 135; });
server.on("/73", []() { server.send(200, "text/html", webPage);  Setting = 135; });
server.on("/72", []() { server.send(200, "text/html", webPage);  Setting = 126; });
server.on("/71", []() { server.send(200, "text/html", webPage);  Setting = 126; });
server.on("/70", []() { server.send(200, "text/html", webPage);  Setting = 126; });

server.on("/69", []() { server.send(200, "text/html", webPage);  Setting = 126; });
server.on("/68", []() { server.send(200, "text/html", webPage);  Setting = 126; });
server.on("/67", []() { server.send(200, "text/html", webPage);  Setting = 117; });
server.on("/66", []() { server.send(200, "text/html", webPage);  Setting = 117; });
server.on("/65", []() { server.send(200, "text/html", webPage);  Setting = 117; });
server.on("/64", []() { server.send(200, "text/html", webPage);  Setting = 117; });
server.on("/63", []() { server.send(200, "text/html", webPage);  Setting = 117; });
server.on("/62", []() { server.send(200, "text/html", webPage);  Setting = 108; });
server.on("/61", []() { server.send(200, "text/html", webPage);  Setting = 108; });
server.on("/60", []() { server.send(200, "text/html", webPage);  Setting = 108; });

server.on("/59", []() { server.send(200, "text/html", webPage);  Setting = 108; });
server.on("/58", []() { server.send(200, "text/html", webPage);  Setting = 108; });
server.on("/57", []() { server.send(200, "text/html", webPage);  Setting = 99; });
server.on("/56", []() { server.send(200, "text/html", webPage);  Setting = 99; });
server.on("/55", []() { server.send(200, "text/html", webPage);  Setting = 99; });
server.on("/54", []() { server.send(200, "text/html", webPage);  Setting = 99; });
server.on("/53", []() { server.send(200, "text/html", webPage);  Setting = 99; });
server.on("/52", []() { server.send(200, "text/html", webPage);  Setting = 90; });
server.on("/51", []() { server.send(200, "text/html", webPage);  Setting = 90; });
server.on("/50", []() { server.send(200, "text/html", webPage);  Setting = 90; });

server.on("/49", []() { server.send(200, "text/html", webPage);  Setting = 90; });
server.on("/48", []() { server.send(200, "text/html", webPage);  Setting = 90; });
server.on("/47", []() { server.send(200, "text/html", webPage);  Setting = 81; });
server.on("/46", []() { server.send(200, "text/html", webPage);  Setting = 81; });
server.on("/45", []() { server.send(200, "text/html", webPage);  Setting = 81; });
server.on("/44", []() { server.send(200, "text/html", webPage);  Setting = 81; });
server.on("/43", []() { server.send(200, "text/html", webPage);  Setting = 81; });
server.on("/42", []() { server.send(200, "text/html", webPage);  Setting = 72; });
server.on("/41", []() { server.send(200, "text/html", webPage);  Setting = 72; });
server.on("/40", []() { server.send(200, "text/html", webPage);  Setting = 72; });

server.on("/39", []() { server.send(200, "text/html", webPage);  Setting = 72; });
server.on("/38", []() { server.send(200, "text/html", webPage);  Setting = 72; });
server.on("/37", []() { server.send(200, "text/html", webPage);  Setting = 63; });
server.on("/36", []() { server.send(200, "text/html", webPage);  Setting = 63; });
server.on("/35", []() { server.send(200, "text/html", webPage);  Setting = 63; });
server.on("/34", []() { server.send(200, "text/html", webPage);  Setting = 63; });
server.on("/33", []() { server.send(200, "text/html", webPage);  Setting = 63; });
server.on("/32", []() { server.send(200, "text/html", webPage);  Setting = 54; });
server.on("/31", []() { server.send(200, "text/html", webPage);  Setting = 54; });
server.on("/30", []() { server.send(200, "text/html", webPage);  Setting = 54; });

server.on("/29", []() { server.send(200, "text/html", webPage);  Setting = 54; });
server.on("/28", []() { server.send(200, "text/html", webPage);  Setting = 54; });
server.on("/27", []() { server.send(200, "text/html", webPage);  Setting = 45; });
server.on("/26", []() { server.send(200, "text/html", webPage);  Setting = 45; });
server.on("/25", []() { server.send(200, "text/html", webPage);  Setting = 45; });
server.on("/24", []() { server.send(200, "text/html", webPage);  Setting = 45; });
server.on("/23", []() { server.send(200, "text/html", webPage);  Setting = 45; });
server.on("/22", []() { server.send(200, "text/html", webPage);  Setting = 36; });
server.on("/21", []() { server.send(200, "text/html", webPage);  Setting = 36; });
server.on("/20", []() { server.send(200, "text/html", webPage);  Setting = 36; });

server.on("/19", []() { server.send(200, "text/html", webPage);  Setting = 36; });
server.on("/18", []() { server.send(200, "text/html", webPage);  Setting = 36; });
server.on("/17", []() { server.send(200, "text/html", webPage);  Setting = 27; });
server.on("/16", []() { server.send(200, "text/html", webPage);  Setting = 27; });
server.on("/15", []() { server.send(200, "text/html", webPage);  Setting = 27; });
server.on("/14", []() { server.send(200, "text/html", webPage);  Setting = 27; });
server.on("/13", []() { server.send(200, "text/html", webPage);  Setting = 27; });
server.on("/12", []() { server.send(200, "text/html", webPage);  Setting = 18; });
server.on("/11", []() { server.send(200, "text/html", webPage);  Setting = 18; });
server.on("/10", []() { server.send(200, "text/html", webPage);  Setting = 18; });  

server.on("/9", []() { server.send(200, "text/html", webPage);   Setting = 18; });
server.on("/8", []() { server.send(200, "text/html", webPage);   Setting = 18; });
server.on("/7", []() { server.send(200, "text/html", webPage);   Setting = 9; });
server.on("/6", []() { server.send(200, "text/html", webPage);   Setting = 9; });
server.on("/5", []() { server.send(200, "text/html", webPage);   Setting = 9; });
server.on("/4", []() { server.send(200, "text/html", webPage);   Setting = 9; });
server.on("/3", []() { server.send(200, "text/html", webPage);   Setting = 9; });
server.on("/2", []() { server.send(200, "text/html", webPage);   Setting = 0; });
server.on("/1", []() { server.send(200, "text/html", webPage);   Setting = 0; });
server.on("/0", []() { server.send(200, "text/html", webPage);   Setting = 0; });

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {

//During very first power on position is set to 254, this sets it to 180  
  if(Position > 180){
    Position = 180;
    EEPROM.write(1, Position);
    EEPROM.commit();
    Setting = 180;
  }

//Saves the current blind setting to EEPROM in case the power is interrupted mid-move
  EEPROM.write(0, Setting);
  delay(5);
  EEPROM.commit();
  delay(5);

//Position less than EEPROM memory
  if(Position < EEPROM.read(0)){
    servoA.write(Position++);
    WriteState = 1; //Write EEPROM when value 1
    delay(5); //How fast the servo moves - larger number moves blinds slower
    Serial.print("Setting: ");  
    Serial.println(EEPROM.read(0));
    Serial.print("Position: ");
    Serial.println(Position);
    Serial.print("Write State: ");
    Serial.println(WriteState);
  }
//Position greater than EEPROM memory
  if(Position > EEPROM.read(0)){
    servoA.write(Position--);
    WriteState = 1; //Write EEPROM when value 1
    delay(5); //how fast the servo moves - larger number moves blinds slower
    Serial.print("Setting: ");  
    Serial.println(EEPROM.read(0));
    Serial.print("Position: ");
    Serial.println(Position);
    Serial.print("Write State: ");
    Serial.println(WriteState);
  }

//***Do not change below here***
  if(Position == EEPROM.read(0)){
    if(WriteState == 1){
      EEPROM.write(1, Position);
      EEPROM.write(0, Setting);
      delay(5);
      EEPROM.commit();
      WriteState = 0;
      delay(5);
      Serial.print("Write State: ");
      Serial.println(WriteState);
    }
  }
server.handleClient();
}
