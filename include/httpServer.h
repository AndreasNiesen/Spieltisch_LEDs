#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include "webPage.h"
#include "commands.h"

class httpServer {
  private:
    WiFiServer server;
    const char* pSsid;
    const char* pPass;

  public:
    httpServer(const char* wifiSsid, const char* wifiPass) {
      pSsid = wifiSsid;
      pPass = wifiPass;
    }

    ~httpServer() {
      server.close();
    }

    void initializeAndStart() {
      WiFi.mode(WIFI_STA);
      WiFi.begin(pSsid, pPass);
      server = WiFiServer(80);

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

    int serve() {
      int returnVal = -1;
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
                Serial.println("header from httpServer.serve:");
                Serial.println(header);
                Serial.println();

                String POSTorGET = header.substring(0, header.indexOf(' '));
                Serial.println("POSTorGET:");
                Serial.println(POSTorGET);
                Serial.println();

                if (POSTorGET.startsWith("POST")) {
                  Serial.println("Completing POST-request.");
                  Serial.println();
                  
                  client.println("HTTP/1.1 202ACCEPTED");
                  client.println("Connection: close");
                  client.println();

                  String cmd = header.substring(header.indexOf(' ') + 1, header.lastIndexOf(' '));
                  Serial.println("cmd:");
                  Serial.println(cmd);
                  Serial.println();

                  cmd.toLowerCase();
                  if (cmd.startsWith("/cmd1")) {
                    returnVal = enum_commands::next;
                    Serial.println("in cmd1");
                    Serial.println();
                  } else if (cmd.startsWith("/cmd2")) {
                    returnVal = enum_commands::previous;
                    Serial.println("in cmd1");
                    Serial.println();
                  } else if (cmd.startsWith("/cmd3")) {
                    returnVal = enum_commands::circle;
                    Serial.println("in cmd1");
                    Serial.println();
                  }

                  break;

                } else {
                  Serial.println("Sending page to Client.");
                  Serial.println();

                  client.println("HTTP/1.1 200OK");
                  client.println("Content-type: text/html");
                  client.println("Connection: close");
                  client.println();

                  client.print(webpage);
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

      return returnVal;
    }
};

#endif