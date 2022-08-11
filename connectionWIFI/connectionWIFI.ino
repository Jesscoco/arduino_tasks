#include "Arduino.h"
#include "ESP8266WiFi.h"

// Definition des entrees sorties
const int led_jaune = 5;

// infos de connexions
const char * SSID = "Redmi1";
const char * PASSWORD = "honeyjj664@";

void setup() {
  //Mise en place d4une liaison serie
  Serial.begin(115200L);
  Serial.println("");
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_jaune, OUTPUT);

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
  Serial.println("Adresse IP : " + WiFi.localIP().toString());
  }
  else{
   digitalWrite(led_jaune,LOW);
   }
  
}
