#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(10, 11); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  delay(3000);
  esp8266.println("AT+CWMODE=3");
  delay(3000);
  esp8266.println("AT+RST");
  delay(3000);
  esp8266.println("AT+CIPMUX=1");
  delay(3000);
  esp8266.println("AT+CIPSERVER=1,5678");
  delay(3000);
  esp8266.println("AT+CIOBAUD=9600");
  delay(3000);
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
      Serial.println("Available");
      if(esp8266.find("play"))
      {
        Serial.println("Ligou!");
      }
      else if(esp8266.find("stop"))
      {
        Serial.println("Desligou!");
      }
    /*while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    } */
    /*if (esp8266.find("+IPD,"))
    {
      delay(300);
      int connectionId = esp8266.read() - 48;
      Serial.println("step1");
 
      String webpage = "<head><meta http-equiv=""refresh"" content=""3"">";
      webpage += "</head><h1><u>ESP8266 - Web Server</u></h1>";
      Serial.println("step2");
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      Serial.println("step3");
      esp8266.println(cipSend);
      delay(1000);
      Serial.println("step4");
      esp8266.println(webpage);
      delay(1000);
      Serial.println("step5");
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
 
      esp8266.println(closeCommand);
      delay(3000);
      Serial.println("step6");
    }*/
    /*else
    {
      while(esp8266.available())
      {
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        Serial.write(c);
      }  
    }*/
  }
  
 
  
  if(Serial.available())
  {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000); 
    
    String command="";
    
    while(Serial.available()) // read the command character by character
    {
        // read one character
      command+=(char)Serial.read();
    }
    esp8266.println(command); // send the read character to the esp8266
  }
}
