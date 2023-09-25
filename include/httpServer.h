#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include "webPage.h"
#include "effects.h"

#include <chrono>

class httpServer {
  private:
    WiFiServer server;
    const char* pSsid;
    const char* pPass;
    int LED_Max;

  public:
    httpServer(const char* wifiSsid, const char* wifiPass) {
      pSsid = wifiSsid;
      pPass = wifiPass;
    }

    ~httpServer() {
      server.close();
    }

    void initializeAndStart(int LED_strip_max_length) {
      WiFi.mode(WIFI_STA);
      WiFi.begin(pSsid, pPass);
      server = WiFiServer(80);

      LED_Max = LED_strip_max_length;

      if (Serial) {
        Serial.print("This boards MAC-Address is ");
        Serial.println(WiFi.macAddress());
        Serial.print("Trying to connect to \"");
        Serial.print(pSsid);
        Serial.println("\"");
        Serial.print("Connecting.");
      }
      while(WiFi.status() != WL_CONNECTED) {
        if (Serial) Serial.print(".");
        delay(500);
      }
      if (Serial) {
        Serial.println();
        Serial.println("Connected!");
        Serial.print("Local IP-Address: ");
        Serial.println(WiFi.localIP());
        Serial.println();
      }
      server.begin();
    }

    Effect* serve() {
      static Effect* retVal = NULL;
      String header = "";
      unsigned long curTime = millis();
      unsigned long prevTime = 0;
      const unsigned long timeOut = 2000;
      
      WiFiClient client = server.available();
      if (client) {
        curTime = millis();
        prevTime = curTime;
        String currentLine = "";
        
        while(client.connected() && curTime - prevTime <= timeOut) {
          curTime = millis();
          if (client.available()) {
            char c = client.read();
            header += c;

            if (c == '\n') {
              if (currentLine.length() == 0) {
                // Serial.println("header from httpServer.serve:");
                // Serial.println(header);
                // Serial.println();

                String POSTorGET = header.substring(0, header.indexOf(' '));
                // Serial.println("POSTorGET:");
                // Serial.println(POSTorGET);
                // Serial.println();

                if (POSTorGET.startsWith("POST")) {
                  String body = client.readString();
                  // Serial.println("POST-Body:");
                  // Serial.println(body);

                  Serial.println("Completing POST-request.");
                  // Serial.println();
                  
                  client.println("HTTP/1.1 202ACCEPTED");
                  client.println("Connection: close");
                  client.println();

                  using std::chrono::high_resolution_clock;
                  using std::chrono::duration_cast;
                  using std::chrono::duration;
                  using std::chrono::milliseconds;

                  auto t1 = high_resolution_clock::now();
                  retVal = get_effect_from_JSON(body, LED_Max);
                  auto t2 = high_resolution_clock::now();

                  /* Getting number of milliseconds as an integer. */
                  int ms_int = duration_cast<milliseconds>(t2 - t1).count();
                  char time[100];
                  itoa(ms_int, time, 10);
                  Serial.println("Dauer get_effect_from_JSON:");
                  Serial.println(time);

                  break;

                } else {
                  // Serial.println("Sending page to Client.");
                  // Serial.println();

                  client.println("HTTP/1.1 200OK");
                  client.println("Content-type: text/html");
                  client.println("Connection: close");
                  client.println();

                  client.print(webpage1 + WiFi.localIP().toString() + webpage2);
                  client.println();

                  break;

                } 
              } else {
                currentLine = "";
              }
            } else if(c != '\r') {
              currentLine += c;
            }
          }
        }
        header = "";
        client.stop();
      }

      return retVal;
    }
};

#endif