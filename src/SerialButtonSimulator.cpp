#include <Arduino.h>
#include <ESPNOW_MASTER.h>
boolean need_send_zero=false;
int need_send_zero_tick=0;
int condition=99;
void SerialCommands(){
    condition=99;
    while(Serial.available()){
        String serial_read = Serial.readString();
        if(serial_read.startsWith("w")){
            //Serial.println("button1: forward");
            condition=1;
        }else if(serial_read.startsWith("s")){
            //Serial.println("button2: backward");
            condition=2;
        }else if(serial_read.startsWith("a")){
            //Serial.println("button3: rotate left");
            condition=3;
        }else if(serial_read.startsWith("d")){
            //Serial.println("button4: rotate right");
            condition=4;
        }else if(serial_read.startsWith("q")){
            //Serial.println("button5: move left");
            condition=5;
        }else if(serial_read.startsWith("r")){
            //Serial.println("button6: move right");
            condition=6;
        }else if(serial_read.startsWith("AW")){
            //Serial.println("button组合: 左前");
            condition=13;
        }else if(serial_read.startsWith("DW")){
            //Serial.println("button组合: 右前");
            condition=14;
        }else if(serial_read.startsWith("AS")){
            //Serial.println("button组合: 左后");
            condition=23;
        }else if(serial_read.startsWith("DS")){
            //Serial.println("button组合: 右后");
            condition=24;
        }
        else if(serial_read.startsWith("M")){
            condition=7;
            //Serial.println("button7: mode switch");
        }else if(serial_read.startsWith("C")){
            condition=8;
            //Serial.println("button8: clear");
        }else if(serial_read.startsWith("D")){
            condition=9;
            //Serial.println("button9: delete");
        }else if(serial_read.startsWith("V")){
            condition=10;
            //Serial.println("button10: volume");
        }else if(serial_read.startsWith("R")){
            condition=11;
            //Serial.println("button11: run");
        }
    }
    if(condition!=99){
        if(condition==7||condition==8||condition==9||condition==10||condition==11){
            char header='0';
            if(condition==7)header='M';
            else if(condition==8)header='C';
            else if(condition==9)header='D';
            else if(condition==10)header='V';
            else if(condition==11)header='R';
            send_data_now(header,condition);
            need_send_zero=false;
            need_send_zero_tick=0;
        }else {
            send_data_now('W',condition);
            need_send_zero=true;
            need_send_zero_tick=0;
        }
    }
  
}