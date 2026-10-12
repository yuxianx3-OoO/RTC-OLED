#include "alarm_edit.h"
#include "rtc.h"
#include "main.h"

void Alarm_Adjust(uint8_t select, uint8_t key)
{
    
    
        
    if (select == 0 )
    {
        if (key == 2)
        {
            alarmTime.Hours = (alarmTime.Hours + 1) % 24; // 调整小时，确保在 0-23 范围内
        }
        else if (key == 3)
        {
            alarmTime.Hours = (alarmTime.Hours + 23) % 24; // 调整小时，确保在 0-23 范围内
        }
    }
    else if (select == 1)
    {
        if (key == 2)
        {
            alarmTime.Minutes = (alarmTime.Minutes + 1) % 60; // 调整分钟，确保在 0-59 范围内
        }
        else if (key == 3)
        {
            alarmTime.Minutes = (alarmTime.Minutes + 59) % 60; // 调整分钟，确保在 0-59 范围内
        }
    }
    else if (select == 2)
    {
        if (key == 2)
        {
            alarmTime.Seconds = (alarmTime.Seconds + 1) % 60; // 调整秒，确保在 0-59 范围内
        }
        else if (key == 3)
        {
            alarmTime.Seconds = (alarmTime.Seconds + 59) % 60; // 调整秒，确保在 0-59 范围内
        }
    }
}    


    
    

        