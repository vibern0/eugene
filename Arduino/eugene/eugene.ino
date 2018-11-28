#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

/* webserver */
ESP8266WebServer server(80);

/* udp */
WiFiUDP Udp;
unsigned int localUdpPort = 4210;

/* lights */
const int rightLightPin = D0;
const int leftLightPin = D1;

/* other states */
bool driving = false;
bool lights = false;

void handleRoot() {
    server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleLights() {
    lights ^= true;
    if(lights) {
        digitalWrite(rightLightPin, HIGH);
        digitalWrite(leftLightPin, HIGH);
        server.send(200, "text/json", "{success:true}");
    } else {
        digitalWrite(rightLightPin, LOW);
        digitalWrite(leftLightPin, LOW);
        server.send(200, "text/json", "{success:false}");
    }
}

void handleDrive() {
    driving ^= true;
    if(driving) {
        startUdp();
        server.send(200, "text/json", "{success:true}");
    } else {
        stopUdp();
        server.send(200, "text/json", "{success:false}");
    }
}

void startWifi() {
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", handleRoot);
    server.on("/lights", handleLights);
    server.on("/drive", handleDrive);
    server.begin();
    Serial.println("HTTP server started");
}

void startUdp() {
    Udp.begin(localUdpPort);
    Serial.printf("Now listening at IP %s, UDP port %d\n",
            WiFi.localIP().toString().c_str(), localUdpPort);
}

void stopUdp() {
    Udp.stop();
    Serial.println("Udp closed.");
}

void setupLightPins() {
    pinMode(rightLightPin, OUTPUT);
    pinMode(leftLightPin, OUTPUT);
}

void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.println();

    setupLightPins();
    startWifi();
    startUdp();
}

void handleDrivingLoop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        char incomingPacket[255];
        char replyPacket[] = "Hi there! Got the message :-)";
        // receive incoming UDP packets
        Serial.printf("Received %d bytes from %s, port %d\n", packetSize,
            Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int len = Udp.read(incomingPacket, 255);
        if (len > 0) {
            incomingPacket[len] = 0;
        }
        Serial.printf("UDP packet contents: %s\n", incomingPacket);

        // send back a reply, to the IP address and port we got the packet from
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(replyPacket);
        Udp.endPacket();
    }
}

void loop() {
    if(driving) {
        handleDrivingLoop();
    }
    server.handleClient();
}
