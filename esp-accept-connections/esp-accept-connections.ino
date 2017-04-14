#include <SoftwareSerial.h>

 /* ports from arduino micro */
SoftwareSerial esp8266(10, 11);


void setup() {

  delay(2000);

  Serial.begin(9600);
  esp8266.begin(115200);

  delay(5000);

  while(1)
  {
    esp8266.println("AT+RST");
    delay(1000);
    
    if (esp8266.find("OK"))
    {
      Serial.println("Module is ready");
      break;
    }
    else {
      Serial.println("ESP8266 Module did not respond.");
      Serial.println("Enter Commands Manually.");
    }
    delay(1000);
  }
  for (int i = 0; i < 5; i++) {

    if (connectWiFi()) {
      break;
    }
  }
  for (int i = 0; i < 5; i++) {

    if (setSingleConnection()) {
      break;
    }
  }
  
}

void loop()
{
  esp8266.println("AT+CWLIF");
  delay(2000);
  while (esp8266.available())
  {
    Serial.write(esp8266.read());
  }
  
}

boolean connectWiFi() {
  esp8266.println("AT+CWMODE=2");
  delay(2000);
  if (esp8266.find("AP")) {
    Serial.println("OK, WiFi ready.");
    return true;
  } else {
    Serial.println("WiFi not ready.");
    return false;
  }
}

boolean setSingleConnection()
{
  esp8266.println("AT+CIPMUX=0");
  delay(2000);
  if (esp8266.find("Single")) {
    Serial.println("OK, set to single connection.");
    return true;
  } else {
    Serial.println("Error setting single connection.");
    return false;
  }
}

