#include "key.h"
#include "gpio.h"

uint8_t Key_GetNum(void)
{
    uint8_t key = 0; // 初始化按键值为 0
    uint16_t pin =0; // 初始化引脚值为 0

    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        key = 1; // 如果 GPIOA 的 PIN1 被按下，设置按键值为 1
        pin = GPIO_PIN_1; // 设置引脚值为 GPIO_PIN_1
    }
    else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
    {
        key = 2; // 如果 GPIOA 的 PIN2 被按下，设置按键值为 2
        pin = GPIO_PIN_2; // 设置引脚值为 GPIO_PIN_2
    }
    else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
    {
        key = 3; // 如果 GPIOA 的 PIN3 被按下，设置按键值为 3
        pin = GPIO_PIN_3; // 设置引脚值为 GPIO_PIN_3
    }
    if (key != 0) // 如果有按键被按下
    {
        HAL_Delay(20); // 延时 20 毫秒，防止按键抖动
        if (HAL_GPIO_ReadPin(GPIOA, pin) == GPIO_PIN_RESET) // 再次检查按键是否仍然被按下
        {
            uint32_t startTick = HAL_GetTick();
            while (HAL_GPIO_ReadPin(GPIOA, pin) == GPIO_PIN_RESET); // 等待按键松开
            if (key == 1 && HAL_GetTick() - startTick >= 1000) // 如果按下时间超过 1000 毫秒
            {
                key = 4; // 设置按键值为 4，表示长按
            } 
        
            return key; // 返回按键值
        }
    }
    return 0; // 如果没有按键被按下，返回 0
}    