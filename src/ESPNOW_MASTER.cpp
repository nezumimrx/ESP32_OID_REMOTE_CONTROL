#include <Arduino.h>
#include <ESPNOW_MASTER.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

boolean connected_with_slave=false;
boolean receive_data_flag=false;
esp_now_peer_info_t peerInfo;
typedef struct data_to_send{
    char x;
    int y;
}   data_to_send;
data_to_send send_data;

typedef struct data_to_recv{
    char x[2];
    int y;
}data_to_recv;
data_to_recv received_data;

void onDataSend(const uint8_t *mac_addr, esp_now_send_status_t sendStatus){
    //char macStr[18];
    // snprintf(macStr,sizeof(macStr),"%02x:%02x:%02x:%02x:%02x:%02x",
    //         mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
    // Serial.println(macStr);
    // Serial.print("send status: ");
    if(sendStatus==0){
        connected_with_slave=true;Serial.println("send success!");
    }else {
        connected_with_slave=false;Serial.println("fail to send");
    }
}

void onDataRecv(const uint8_t *mac,const uint8_t *incomingData, int len){
    receive_data_flag=true;
    memcpy(&received_data, incomingData, sizeof(received_data));
    //Serial.print("x: ");
    //Serial.println(received_data.x);
    //Serial.print("y: ");
    //Serial.println(received_data.y);
    //Serial.println();

}


void espnow_master_init(){
    WiFi.mode(WIFI_STA);
    esp_wifi_set_mac(WIFI_IF_STA,&masteraddress[0]);
    Serial.print("current master address: ");
    Serial.println(WiFi.macAddress());
    WiFi.disconnect();
    if(esp_now_init()!=0){
        Serial.println("ESPNOW fail to start!");
        return;
    }
    esp_now_register_send_cb(onDataSend);
    memcpy(peerInfo.peer_addr,otherguy,6);
    peerInfo.channel=0;
    peerInfo.encrypt=false;
    if(esp_now_add_peer(&peerInfo)!=ESP_OK){
        Serial.println("failed to add peer");
    }
    esp_now_register_recv_cb(onDataRecv);

}
void send_data_now(char c , int num){
    send_data.x=c;
    send_data.y=num;
    esp_now_send(otherguy,(uint8_t*)&send_data,sizeof(send_data));
}