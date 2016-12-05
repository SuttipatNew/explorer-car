#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d47461487fe24c2bac9d7b04d72c9439";
//char ssid[] = "KUWIN";
//char password[] = "";
//const char* ssid = "Booktay2.4";
//const char* password = "5732639423";
const char* ssid = "Booktay";
const char* password = "12345678";

Servo servo;

void move(int x, int y) {
  if (y > 512) {
    Serial.println("up");
  } else if (y < 512) {
    Serial.println("down");
  } else if (x > 512) {
    Serial.println("right");
  } else if (x < 512) {
    Serial.println("left");
  } else {
    Serial.println("other");
  }
}

void setup()
{
  Serial.begin(115200);
  
  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);


  Blynk.begin(auth, ssid, password);

//  while (Blynk.connect() == false) {
//    // Wait until connected
//  }
  servo.attach(4);
  
}

BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  // Do sometxhing with x and y
  Blynk.virtualWrite(V4, x);
  move(x, y);
}

BLYNK_WRITE(V2) {
  int x = param.asInt();
  servo.write(x);
}

BLYNK_WRITE(V3) 
{
    if (param.asInt() == 1) {
        //HIGH
        Blynk.email("Subject: Button Logger", "You just pushed the button..."); 
        Blynk.notify("Blynk : alert");        
        Blynk.tweet("Blynk Test : Sending");
    }
}

void loop()
{
  Blynk.run();
}

