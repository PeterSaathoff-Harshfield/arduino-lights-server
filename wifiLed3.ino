// #pragma once

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 

#include "Controller.h"
#include "Light.h"

int redPin = 3;
int greenPin = 5;
int bluePin = 6;

Light light(redPin, greenPin, bluePin);
Controller controller = Controller();

// bool on = true;
int currentColor[3] = {100, 100, 100};

long currentTime = millis();
long lastTime = millis();

// store these in a file called "arduino_secrets.h" with #DEFINE SECRET_SSID etc.
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;

//http headers and response bodies

char* htmlHeader =
"HTTP/1.1 202 OK\n\
Content-Type: text/html\n\
Connection: close\n\
\n";

extern char index[];

char* jsonHeader =
"HTTP/1.1 200 OK\n\
Content-Type: text/json\n\
Connection: close\n\
\n";

char jsonResponse[512];

//memory monitoring
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;
int freeMemory() {
 int free_memory;

 if ((int)__brkval == 0)
   free_memory = ((int)&free_memory) - ((int)&__bss_end);
 else
   free_memory = ((int)&free_memory) - ((int)__brkval);

 return free_memory;
}

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  light.set(100, 100, 100);
  light.display();
  
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }
  
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


// int number = 0;

void loop() {
  if (controller.on()) {
    
    currentTime = millis();
    if (lastTime < currentTime - 20) {
      controller.update(currentTime);
      light.set(controller.r, controller.g, controller.b);
      lastTime = millis();
      light.display();
    }
  }
  else {
    light.set(0, 0, 0);
    light.display();
  }
  
  
  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    
    String entireHeader = "";
    String url = "";
    boolean gotPathLine = false;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (!gotPathLine) {
          url += c;
        }
        entireHeader += c;
        
        if (c == '\n' && currentLineIsBlank) {
          Serial.println(url);
          url = url.substring(4, url.length()-11);
          Serial.println(url);
          
          char b[128];
          
          String path;
          // String whiteLevel;
  
          int c1 = 0;
          char* token1;
          char* t1 = strtok_r(url.c_str(), "?", &token1);
          while (t1) {
            // Serial.print("c1: ");
            // Serial.println(c1);
            // Serial.println(String(t1));
            
            // String p;
            // if (t1[0] == '/') {
            //   path = String(t1);
            //   Serial.println(path);
            // }
            
            path = String(t1);
            if (path == "/json") {
              client.println(jsonHeader);
              controller.jsonState(jsonResponse, sizeof(jsonResponse));
              // Serial.println(jsonResponse);
              client.println(jsonResponse);
              // Serial.println("doing json thing");
            }
            if (path == "/powerToggle") {
              // Serial.println("this should be toggling power");
              // Serial.println("toggling power");
              controller.powerToggle();
              Serial.println("doing power thing");
              delay(1);
            }
            if (path == "/white") {
              // Serial.println("found white");
              // Serial.println(p);
              controller.setMode(1);
            }
            if (path == "/spectrum") {
              controller.setMode(2);
            }
            if (path == "/solidColors") {
              controller.setMode(3);
            }
            if (path == "/gradient") {
              controller.setMode(4);
            }
            if (path == "/random") {
              controller.setMode(5);
            }
            if (path == "/flow") {
              controller.setMode(6);
            }
            if (path == "/red") {
              controller.setMode(7);
            }
            if (path == "/arbitrary") {
              controller.setMode(8);
            }

      
            int c2 = 0;
            char* token2;
            char* t2 = strtok_r(t1, "&", &token2);
            while (t2) {
              // Serial.print("c2: ");
              // Serial.println(c2);
              // Serial.println(String(t2));
      
      
              
              String key;
              String value;
              int c3 = 0;
              char* token3;
              char* t3 = strtok_r(t2, "=", &token3);
              while (t3) {
                // Serial.print("c3: ");
                // Serial.println(c3);
                // Serial.println(String(t3));
        
                if (c3 == 0) {
                  key = String(t3);
                }
                if (c3 == 1) {
                  value = String(t3);
                }
        
                t3 = strtok_r(NULL, "=", &token3);
                c3++;
              }
              // Serial.print("key: ");
              // Serial.println(key);
              // Serial.print("value: ");
              // Serial.println(value);
      
              if (key == "white") {
                // whiteLevel = value;
                int br = value.toInt();
                controller.setWhite(br);
              }
              if (key == "solidcolormode") {
                Serial.println("found solid color mode setting!!!");
                int scm = value.toInt();
                controller.setSolidColorMode(scm);
              }
              if (key == "randomrate") {
                int rr = value.toInt();
                controller.setRandomRate(rr);
              }
              if (key  == "randommax") {
                int rm = value.toInt();
                controller.setRandomMaxBrightness(rm);
              }
              if (key == "spectrumrate") {
                int sr = value.toInt();
                controller.setSpectrumRate(sr);
              }
              if (key == "spectrummax") {
                int sb = value.toInt();
                controller.setSpectrumBrightness(sb);
              }
              if (key == "gradientmode") {
                int gm = value.toInt();
                controller.setGradientMode(gm);
              }
              if (key == "gradientrate") {
                int gr = value.toInt();
                controller.setGradientRate(gr);
              }
              if (key == "gradientbrightness") {
                int gb = value.toInt();
                controller.setGradientBrightness(gb);
                Serial.println(gb);
              }
              if (key == "flowrate") {
                int fr = value.toInt();
                controller.setFlowRate(fr);
              }
              if (key == "flowmax") {
                int fm = value.toInt();
                // Serial.println("got flow max!!!");
                controller.setFlowMaxBrightness(fm);
              }
              if (key == "redpulserate") {
                int rpr = value.toInt();
                controller.setRedPulseRate(rpr);
              }
              if (key == "arbitraryr") {
                int ar = value.toInt();
                controller.setArbitraryR(ar);
              }
              if (key == "arbitraryg") {
                int ag = value.toInt();
                controller.setArbitraryG(ag);
              }
              if (key == "arbitraryb") {
                int ab = value.toInt();
                controller.setArbitraryB(ab);
              }
              if (key == "arbitraryhue") {
                int ah = value.toInt();
                controller.setArbitraryHue(ah);
              }
      
              t2 = strtok_r(NULL, "&", &token2);
              c2++;
            }
            t1 = strtok_r(NULL, "?", &token1);
            c1++;
          }
  
          // Serial.print("url: ");
          // Serial.println(url);
          // Serial.print("path: ");
          // Serial.println(path);
          // Serial.print("white level: ");
          // Serial.println(whiteLevel);
  
          
          //monitor incoming requests
          // Serial.print("path: ");
          // Serial.println(path);
          
          if (path == "/") {
            client.println(htmlHeader);
            client.println(index);
          }
          else {
            // if (path == "/powerToggle") {
            //   on = !on;
            // }
            // if (path == "/white") {
              // controller.setMode(0);
            // }
            // if (path == "/spectrum") {
            //   controller.setMode(1);
            // }
            // if (path == "/solidColors") {
            //   controller.setMode(2);
            // }
            // if (path == "/gradient") {
            //   controller.setMode(3);
            // }
            // if (path == "/random") {
            //   controller.setMode(4);
            // }
            // if (path == "/flow") {
            //   controller.setMode(5);
            // }
            // if (path == "/red") {
            //   controller.setMode(6);
            // }
            if (path == "/left") {
              controller.adjustMode('l');
            }
            if (path == "/right") {
              controller.adjustMode('r');
            }
            

            // client.println(jsonHeader);
            // controller.jsonState(jsonResponse, sizeof(jsonResponse));
            // // Serial.println(jsonResponse);
            // client.println(jsonResponse);
            
          }
          
          break;
        }
        
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          gotPathLine = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    Serial.println(entireHeader);
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();

    //monitor the arduino's memort usage
    // Serial.print("free memory");
    // Serial.println(freeMemory());

  }
}



void handleUrl(char* url) {
  
}




// void buildJsonResponse() {
//   char r[512];
//   char* onString;
//   char* powerButtonString;
//   if (controller.on()) {
//     onString = "On";
//     powerButtonString = "Turn Off";
//   }
//   else {
//     onString = "Off";
//     powerButtonString = "Turn On";
//   }
//   sprintf(r, "{\"number\": %d, \"powerStatus\": \"%s\", \"powerButtonText\": \"%s\", \"r\": %d, \"g\": %d, \"b\": %d}", number, onString, powerButtonString, controller.r, controller.g, controller.b);
//   jsonResponse = r;
// }




void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
