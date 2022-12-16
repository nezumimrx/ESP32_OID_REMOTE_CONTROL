#include <Arduino.h>
#include <ESPNOW_MASTER.h>
#include <SerialButtonSimulator.h>
#include <Global_vars.h>
#include <Button_funcs.h>

TaskHandle_t TICK_TASK_HANDLE;

void TICK_TASK(void*parameters){
  for(;;){
    if(need_send_zero==true){
      need_send_zero_tick++;
      if(need_send_zero_tick>=5){
        need_send_zero=false;
        need_send_zero_tick=0;
        send_data_now('W',0);
        //Serial.println("button up: send 0");
      }
    }
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(25);
  Button_init();
  espnow_master_init();
  xTaskCreate(TICK_TASK,"TICK_TASK",10000,NULL,1,&TICK_TASK_HANDLE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Button_read();
  SerialCommands();
}