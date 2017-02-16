#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
  const char* ssid = "BMW";
const char* password = "password";

ESP8266WebServer server(80);

String webPage = "";

int lmotor1 = 12,lmotor2 = 14,rmotor1 = 15,rmotor2 = 13;


void setup(void){
  webPage += "<head> <title> Veneeth Raj </title> <style> table, td { padding:20px;} button{ padding:15px; background-color:black; color:red; width:150px; } h1{ text-align:center; font-size:50px; color:#ff3333; font-family:calibri; } h3{ text-align:center; font-family:Segoe Print; color:#8c1aff; } body { background-color:#00bfff; } span{ margin-left:448px; } p{ margin-left:600px } </style> </head> <body> <h1>BOT CONTROL USING WIFI MODULE ESP8266</h1><br><br> <p> <a href=\"forward\"><button>FORWARD</button></a> </p> <span> <a href=\"left\"><button >LEFT</button></a> <a href=\"stop\"><button >STOP</button></a> <a href=\"right\"><button >RIGHT</button></a> </span> <p> <a href=\"backward\"><button >BACKWARD</button></a> </p> <br><br><br><br> <h3>UPGRADED</h3> </body> ";
  // preparing GPIOs
  pinMode(lmotor1, OUTPUT);
  pinMode(lmotor2, OUTPUT);
  pinMode(rmotor1, OUTPUT);
  pinMode(rmotor2, OUTPUT);
  digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, LOW);
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/forward", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(lmotor1, HIGH);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, HIGH);
  digitalWrite(rmotor2, LOW);
    delay(1000);
  });
  server.on("/backward", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, HIGH);
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, HIGH);
    delay(1000); 
  });
  server.on("/left", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, HIGH);
  digitalWrite(rmotor2, LOW);
    delay(1000);
  });
  server.on("/right", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(lmotor1, HIGH);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, LOW);
    delay(1000); 
  });
  server.on("/stop", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
