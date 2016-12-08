#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <SPI.h>
#include <SimpleTimer.h>
#include <DHT.h>

#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define DHTPIN 4   
#define DHTTYPE DHT11

char auth[] = "efff2dc9f1bb4b09bda5bf2659705c07";
//char ssid[] = "KUWIN";
//char password[] = "";
//const char* ssid = "Booktay";
//const char* password = "12345678";
char ssid[] = "D-Link home network";
char password[] = "Home025611592";

Servo servo;
WidgetTerminal terminal(V0);

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V9, t);
  Blynk.virtualWrite(V10, h);
}


void move(int x, int y) {
  if (y > 512) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else if (y < 512) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else if (x > 512) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else if (x < 512) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, password);
  
  while (Blynk.connect() == false) {
    // Wait until connected
  }
  
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.print(F("Blynk Connected - IP :"));
  terminal.println(WiFi.localIP());
  terminal.flush();
  
  servo.attach(D4);
  dht.begin();
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

String data = "";

void getValUltra() {
    data = Serial.readString();
    if(data == NULL) {
      Serial.println("null");
    }
    Serial.print("nork loop: ");
    Serial.print(data);
    Serial1.flush();
}


void loop()
{
  sendSensor();
  Blynk.run();
}

BLYNK_WRITE(V0)
{    
    if (String("dist") == param.asStr()) {
        terminal.print("Distance : ");
        terminal.print(data);
        terminal.print(" Meter ");        
    } else if(String("tweet") == param.asStr()) {
        terminal.println("Send Tweet");                    
        Blynk.tweet("Blynk : NodeMCU Start");
    } else if(String("mail") == param.asStr()) {
        terminal.println("Send Mail");
        Blynk.email("Blynk : NodeMCU ", "NodeMCU Start");  
    } else if(String("up") == param.asStr()) {
        terminal.println("up");
        move(512,1000); 
    } else if(String("down") == param.asStr()) {
        terminal.println("down");
        move(512,100); 
    } else if(String("left") == param.asStr()) {
        terminal.println("left");
        move(100,512); 
    } else if(String("right") == param.asStr()) {
        terminal.println("right");
        move(1000,512); 
    } else if(String("stop") == param.asStr()) {
        terminal.println("stop");
        move(512,512); 
    } else if(String("ip") == param.asStr()) {
        terminal.print("IP :");
        terminal.println(WiFi.localIP());
    } else {
        terminal.write(param.getBuffer(), param.getLength());
        terminal.println();
    }
    terminal.flush(); 
}

BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  move(x,y);
}

BLYNK_WRITE(V2) {
  int sv = param.asInt();
  servo.write(sv);
}

BLYNK_WRITE(V3) {
  if(param.asInt() == 1) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
  
}

BLYNK_WRITE(V4) {
  if(param.asInt() == 1) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
  
}

BLYNK_WRITE(V5) {
  if(param.asInt() == 1) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
  
}

BLYNK_WRITE(V6) {
  if(param.asInt() == 1) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(D7, LOW);
  }
  
}

BLYNK_WRITE(V7) {
  if(param.asInt() == 1) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
  } else {
    digitalWrite(D7, LOW);
  }
  
}

BLYNK_READ(V8) {
    Blynk.virtualWrite(V8,data);
}

//BLYNK_READ(V9) {
//  
//}
//
//BLYNK_READ(V10) {
//  
//}



