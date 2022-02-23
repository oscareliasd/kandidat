#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
 
const char* ssid = "TEST";
const char* pass = "123456789";
 
WiFiServer server(23);
WiFiClient client;
//uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE4,0x84,0x34}; //MAC-adress till den svarta
//uint8_t broadcastAdress[] = {0x7C,0x9E,0xBD,0x60,0xD1,0x8C}; //MAC till den med kondensatorn
uint8_t broadcastAdress[] = {0X7C,0X9E,0XBD,0X61,0X58,0XF4}; //MAC till den med vit tejp
String success;

typedef struct struct_message{ //Denna preppar vad för typ av data som ska tas emot
  int test1;
  int test2;
  int test3;
  int test4;
  int test5;
  int test6;
  int test7;
  int test8;
  int test9;
  int test10;
  int test11;
  int test12;
  int test13;
  int test14;
  int test15;
}struct_message;
 
struct_message test;
struct_message rcv_msg;

int rcvINT;
String rcvMESSAGE;

// Callback when data is sent (används ej av denna)
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}


// Callback when data is received, denna triggas av mottaget meddlande
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&rcv_msg, incomingData, sizeof(rcv_msg));
  Serial.print("Bytes received: ");
  Serial.println(len);

  Serial.println("Values: ");
  Serial.println(rcv_msg.test1);
  Serial.println(rcv_msg.test2);
  Serial.println(rcv_msg.test3);
  Serial.println(rcv_msg.test4);
  Serial.println(rcv_msg.test5);
  Serial.println(rcv_msg.test6);
  Serial.println(rcv_msg.test7);
  Serial.println(rcv_msg.test8);
  Serial.println(rcv_msg.test9);
  Serial.println(rcv_msg.test10);
  Serial.println(rcv_msg.test11);
  Serial.println(rcv_msg.test12);
  Serial.println(rcv_msg.test13);
  Serial.println(rcv_msg.test14);
  Serial.println(rcv_msg.test15);

}
 
void getMACAdress(){
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}
 
 
void setup() {
  Serial.begin(115200);
  delay(100);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  esp_now_register_send_cb(OnDataSent);
 
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAdress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
 
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
 
}
 
void getMessage(){
}
 
void loop() {
  //esp_err_t result = esp_now_send(broadcastAdress, (uint8_t *) &test, sizeof(test));
  //delay(10);
}