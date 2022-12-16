#include <Arduino.h>
#include <Global_vars.h>
#include <ESPNOW_MASTER.h>
#define forward_pin 16
#define backward_pin 17
#define turn_left_pin 21
#define turn_right_pin 22
#define mec_left 14
#define mec_right 25
#define button_clear 26
#define button_play 32
#define button_back 33
#define mode_switch 13
#define volume_pin 12

#define DEBUG 1
String button_readStr_previous="";
boolean need_send_zero_after_button_release=false;
void Button_init(){
    pinMode(15,OUTPUT);//连接指示灯
    pinMode(forward_pin,INPUT_PULLUP);
    pinMode(backward_pin,INPUT_PULLUP);
    pinMode(turn_left_pin,INPUT_PULLUP);
    pinMode(turn_right_pin,INPUT_PULLUP);
    pinMode(mec_left,INPUT_PULLUP);
    pinMode(mec_right,INPUT_PULLUP);
    pinMode(button_clear,INPUT_PULLUP);
    pinMode(button_play,INPUT_PULLUP);
    pinMode(button_back,INPUT_PULLUP);
    pinMode(mode_switch,INPUT_PULLUP);
    pinMode(volume_pin,INPUT_PULLUP);

}

String button_read_add_to_str(String &str, int pin){
    uint8_t read_data = digitalRead(pin);
    str +=read_data;
    return str;
}

void Button_read(){
    String button_readStr="";//111111 1clear 1play 1back 1mode 1volume
    button_read_add_to_str(button_readStr,forward_pin);
    button_read_add_to_str(button_readStr,backward_pin);
    button_read_add_to_str(button_readStr,turn_left_pin);
    button_read_add_to_str(button_readStr,turn_right_pin);
    button_read_add_to_str(button_readStr,mec_left);
    button_read_add_to_str(button_readStr, mec_right);
    button_read_add_to_str(button_readStr, button_clear);
    button_read_add_to_str(button_readStr, button_play);
    button_read_add_to_str(button_readStr, button_back);
    button_read_add_to_str(button_readStr,mode_switch);
    button_read_add_to_str(button_readStr,volume_pin);
    //Serial.print("button_readStr: ");Serial.println(button_readStr);
    
        if(button_readStr=="01111111111"){
            if(DEBUG)Serial.println("forward");
            send_data_now('W',1);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="10111111111"){
            if(DEBUG)Serial.println("backward");
            send_data_now('W',2);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="11011111111"){
            if(DEBUG)Serial.println("rotate left");
            send_data_now('W',3);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="11101111111"){
            if(DEBUG)Serial.println("rotate right");
            send_data_now('W',4);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="11110111111"){
            if(DEBUG)Serial.println("mec left");
            send_data_now('W',5);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="11111011111"){
            if(DEBUG)Serial.println("mec right");
            send_data_now('W',6);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="11111011111"){
            if(DEBUG)Serial.println("mec right");
            send_data_now('W',6);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="01011111111"){
            if(DEBUG)Serial.println("forward left");
            send_data_now('W',13);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="01101111111"){
            if(DEBUG)Serial.println("forward right");
            send_data_now('W',14);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="10011111111"){
            if(DEBUG)Serial.println("back left");
            send_data_now('W',23);
            need_send_zero_after_button_release=true;
        }else if(button_readStr=="10101111111"){
            if(DEBUG)Serial.println("back right");
            send_data_now('W',24);
            need_send_zero_after_button_release=true;
        }
        
        
        else if(button_readStr=="11111101111"){
            if(DEBUG)Serial.println("clear");
            send_data_now('C',0);
        }else if(button_readStr=="11111110111"){
            if(DEBUG)Serial.println("play");
            send_data_now('R',0);
        }else if(button_readStr=="11111111101"){
            if(DEBUG)Serial.println("mode");
            send_data_now('M',0);
        }else if(button_readStr=="11111111011"){
            if(DEBUG)Serial.println("back");
            send_data_now('D',0);
        }else if(button_readStr=="11111111110"){
            if(DEBUG)Serial.println("volume");
            send_data_now('V',0);
        }
    
    if(need_send_zero_after_button_release==true&&button_readStr=="11111111111"){
        Serial.println("zero");
        send_data_now('W',0);
        delayMicroseconds(5000);
        send_data_now('W',0);
        delayMicroseconds(5000);
        send_data_now('W',0);
        need_send_zero_after_button_release=false;
    }





    button_readStr_previous=button_readStr;
    delayMicroseconds(15000);
}












