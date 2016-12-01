#include <ESP8266WiFi.h>
#define D5 14
#define D6 12
#define D7 13
#define D8 15

const char* ssid = "D-Link home network";
const char* password = "Home025611592";
//const char* ssid = "KUWIN";
//const char* password = "";
//const char* ssid = "HUAWEI_P9lite_8928";
//const char* password = "12345678";

WiFiServer server(80);
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
  
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
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

void loop() {
  String request = getRequest();
  if(request != "") {
    Serial.println(request);
    move(request);
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
