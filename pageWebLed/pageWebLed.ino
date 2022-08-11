#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"


// Definition des entrees sorties
const int led_jaune = 5;
const int led_verte = 4;

// Page html
const char index_html[] PROGMEM = R"=====(
  <!=doctype html>
  <html>
    <head>
      <title> Commande LED</title>
    </head>
    <body>
      <a href="/switchLedOn">
        <button> Switch ON </button>
      </a>
      <a href="/switchLedOff">
        <button> Switch OFF </button>
      </a>
    </body>
  </html>
)=====";


// creer un objet WebServer
ESP8266WebServer serverWeb(80);

// infos de connexions
const char * SSID = "Redmi1";
const char * PASSWORD = "honeyjj664@";

//Def fonctions serveur Web
void switchLedOn(){
  digitalWrite(led_verte, HIGH);  
  handleRoot();
}
void switchLedOff(){
  digitalWrite(led_verte, LOW);  
  handleRoot(); 
}
void handleRoot(){
  serverWeb.send(200,"text/html", index_html);
}
void setup() {
  //Mise en place d4une liaison serie
  Serial.begin(115200L);
  Serial.println("");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_jaune, OUTPUT);
  pinMode(led_verte, OUTPUT);
  
  //mise en place du serverWeb
  serverWeb.on("/switchLedOn", switchLedOn);
  serverWeb.on("/switchLedOff", switchLedOff);
  serverWeb.on("/index.html", handleRoot);
  serverWeb.on("/",handleRoot);
  serverWeb.begin();
  // mode de connexion
  WiFi.mode(WIFI_STA);
  // start connexion
  WiFi.begin(SSID, PASSWORD);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //tester l'etat de la connexion
  // si l'object est connecte au reseau on effectue les taches
  if(WiFi.isConnected()){
    digitalWrite(led_jaune,HIGH);
    serverWeb.handleClient();
  }
  else{
   digitalWrite(led_jaune,LOW);
   }
  
}
