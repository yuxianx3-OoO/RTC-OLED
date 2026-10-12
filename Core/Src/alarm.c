#include "alarm.h"

static uint8_t alarmOn = 0; // 静态变量，表示闹钟状态，0 表示关闭，1 表示开启
static uint8_t lastAlarmState = 0; // 静态变量，记录上一次的闹钟状态

void Alarm_Check(RTC_TimeTypeDef now, RTC_TimeTypeDef alarmTime)//判断到没到
{
    // 检查当前时间是否与闹钟时间匹配
    if (now.Hours == alarmTime.Hours && now.Minutes == alarmTime.Minutes && now.Seconds == alarmTime.Seconds)
    {
        if (!lastAlarmState) // 如果上一次状态是关闭的
        {
            alarmOn = 1; // 设置闹钟状态为开启
            lastAlarmState = 1; // 更新上一次状态为开启
        }
    }
    else
    {
        lastAlarmState = 0; // 如果时间不匹配，重置上一次状态为关闭
    }
}

uint8_t Alarm_IsOn(void)//获取当前报警状态
{
    return alarmOn;
}

void Alarm_Stop(void)
{
    alarmOn = 0; // 停止闹钟，将状态设置为关闭
    lastAlarmState = 0; // 同时重置上一次状态

}
