#ifndef ALARM_EDIT_H
#define ALARM_EDIT_H

#include "main.h" // 必须包含，因为 RTC_TimeTypeDef 定义在这个头文件链里
extern RTC_TimeTypeDef alarmTime; // 声明 alarmTime 变量为外部变量
void Alarm_Adjust(uint8_t select, uint8_t key);

#endif