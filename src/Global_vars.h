#include <Arduino.h>
extern boolean need_send_zero;//为了模仿宇鑫遥控器发送完动作指令后发送00 0000 0000，所以这里通过计时器实现，
extern int need_send_zero_tick;//每发送一次命令之后，need_send_zero变为true，在计时器中need_send_zero_tick开始以10ms为单位计时，超过5次，即50ms后发送00 0000 0000