#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define D5 14
#define D6 12
#define D7 13
#define D8 15

//const char* ssid = "D-Link home network";
//const char* password = "Home025611592";
//const char* ssid = "KUWIN";
//const char* password = "";
//const char* ssid = "HUAWEI_P9lite_8928";
//const char* password = "12345678";
const char* ssid = "Booktay";
const char* password = "12345678";

char auth[] = "d47461487fe24c2bac9d7b04d72c9439";

WiFiServer server(80);
WiFiClient client;

Servo servo;

void move(int x, int y) {
  if (y > 512) {
    Serial.println("up");
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else if (y < 512) {
    Serial.println("down");
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else if (x > 512) {
    Serial.println("right");
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else if (x < 512) {
    Serial.println("left");
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else {
    Serial.println("still");
    digitalWrite(D7, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());

  Blynk.begin(auth, ssid, password);
  

//  while (Blynk.connect() == false) {
//     Wait until connected
//    Serial.print(".");
//  }

//  server.begin();
//  Serial.println("Server started");
  
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  servo.attach(4);
}

void move(String request) {
  if(request.indexOf("DIR=UP") != -1) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else if(request.indexOf("DIR=DOWN") != -1) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else if(request.indexOf("DIR=LEFT") != -1) {
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
  } else if(request.indexOf("DIR=RIGHT") != -1) {
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
  } else if(request.indexOf("DIR=STILL") != -1) {
    digitalWrite(D7, LOW);
  }
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


void loop() {
  Blynk.run();
  String request = getRequest();
  if(request != "") {
    Serial.println(request);
    move(request);
//    Serial1.println(request);
  }
}

String getRequest() {
  WiFiClient client = server.available();
  String data;
  if(client.connected()) {
    data = client.readStringUntil('\r');
    client.flush();
  }
  if(client.connected()) {
    client.print("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<note>\n  <from>Jani</from>\n  <to>Tove</to>\n  <message>Remember me this weekend</message>\n</note>\n");
  }
  return data;
}
