#include "time_edit.h"
#include "rtc.h"

void Time_Adjust(uint8_t select, uint8_t key)
{
    RTC_TimeTypeDef now = {0};
    HAL_RTC_GetTime(&hrtc, &now, RTC_FORMAT_BIN);
        
    if (select == 0 )
    {
        if (key == 2)
        {
            now.Hours = (now.Hours + 1) % 24; // 调整小时，确保在 0-23 范围内
        }
        else if (key == 3)
        {
            now.Hours = (now.Hours + 23) % 24; // 调整小时，确保在 0-23 范围内
        }
    }
    else if (select == 1)
    {
        if (key == 2)
        {
            now.Minutes = (now.Minutes + 1) % 60; // 调整分钟，确保在 0-59 范围内
        }
        else if (key == 3)
        {
            now.Minutes = (now.Minutes + 59) % 60; // 调整分钟，确保在 0-59 范围内
        }
    }
    else if (select == 2)
    {
        if (key == 2)
        {
            now.Seconds = (now.Seconds + 1) % 60; // 调整秒，确保在 0-59 范围内
        }
        else if (key == 3)
        {
            now.Seconds = (now.Seconds + 59) % 60; // 调整秒，确保在 0-59 范围内
        }
    }
    HAL_RTC_SetTime(&hrtc, &now, RTC_FORMAT_BIN); // 设置新的时间
}

        