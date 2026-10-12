#ifndef ALARM_H
#define ALARM_H

#include "rtc.h"

void Alarm_Check(RTC_TimeTypeDef now, RTC_TimeTypeDef alarmTime);//判断是否到达闹钟时间
uint8_t Alarm_IsOn(void); //获取当前报警状态
void Alarm_Stop(void);

#endif