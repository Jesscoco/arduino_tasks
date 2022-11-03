/*============================================================================================================================
 * ------------------------------------------------Dun%-----ESP32 CAM - QRCODE----%al----------------------------------------*
 ============================================================================================================================*/


/**=========================Library=========================**/
#include <HTTPClient.h>
#include <ESP32QRCodeReader.h>
#include <WiFi.h>
#include <Arduino.h>
#include "esp_camera.h"
//
/*--------------------------------Configuration Wifi**/
const char* ssid = "MOOVAFRICABJMW45V_7D7F";
const char* password = "01376054";




/*-------------------------------- IOt Configuration**/
const String BASE_URL   = "http://192.168.1.113:8000/etudiants/getqrcode";

/**=========================variables=========================**/
int buzzer=4;/*Buzzer*/
String lienQR = "";
String lastQR= ""; 
unsigned long k;
int temps = 300000;
/**=========================Ojects/Structure=========================**/
ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
struct QRCodeData qrCodeData;
HTTPClient httpClient;
 

/**_____________________________Void Setup_____________________________**/
void setup(){
  Serial.begin(115200);
  Serial.println("System on");
  delay(500);
  pinMode(buzzer,OUTPUT);
  for(int i=0; i<3 ; i++){
   digitalWrite(buzzer, HIGH);
   delay(100);
   digitalWrite(buzzer, LOW);
   delay(500);
  }
/*Configuration de la caméra*/
  camera_config_t config;
  if(psramFound()){
    config.frame_size = FRAMESIZE_CIF;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_HQVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  } 
   
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  reader.setup();
  reader.begin();
  Serial.println("System ready");
 
  digitalWrite(buzzer, HIGH);
  delay(1500);
  digitalWrite(buzzer, LOW);
  
  k=millis();
   
}


/**_____________________________Void Loop_____________________________**/
void loop(){

      /*Si un Code QR est détecté*/
   if (reader.receiveQrCode(&qrCodeData, 50)){
      Serial.println("Found QRCode");
      if (qrCodeData.valid){ //si le code est valide
        lienQR = (const char *)qrCodeData.payload;
        Serial.print("Payload: ");
        Serial.println(lienQR);
      }
      else{
        Serial.print("Invalid: ");
        lienQR = (const char *)qrCodeData.payload;
        Serial.println(lienQR);
        for(int i=0; i<=3 ; i++){
          digitalWrite(buzzer, HIGH);
          delay(80);
          digitalWrite(buzzer, LOW);
          delay(80);
        }
    }
  }

  /**********************Récupération de la valeur du code qR********************/
  if((lienQR !="")&&(lienQR !="ECC failure")&&(lienQR !="Format data ECC failure")&&(lienQR !="Invalid version")){
    Serial.println("Code enregistré");
       if(lienQR != lastQR){
        /*un bip du buzzer pour notifier que le code QR est recupéré*/
          digitalWrite(buzzer, HIGH);
          delay(500);
          digitalWrite(buzzer, LOW);
        
          Serial.print("LienQR = ");
          Serial.println(lienQR);
          P_IOT_fonc(lienQR);
          lastQR=lienQR;
          lienQR = "";
          Serial.println("fin iot");
        }else{
          if(millis()-k>temps){
            digitalWrite(buzzer, HIGH);
            delay(500);
            digitalWrite(buzzer, LOW);
          
            Serial.print("LienQR = ");
            Serial.println(lienQR);
            P_IOT_fonc(lienQR);
            lastQR=lienQR;
            lienQR = "";
          }else{
            Serial.println("Même code");
            lienQR="";
            for(int i=0; i<=1 ; i++){
                digitalWrite(buzzer, HIGH);
                delay(80);
                digitalWrite(buzzer, LOW);
                delay(80);
              }
           }
        }
  }
}

void P_IOT_fonc(String p1){
  String requette;
  WiFiClient client;
  
  String post_url = BASE_URL + "/" +p1;     
                         
  Serial.println(post_url);
  httpClient.begin (client,post_url);                 
  int httpCode=httpClient.GET();                      

    
 }
