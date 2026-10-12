/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "stm32f1xx_hal_gpio.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "OLED.h"
#include "key.h"
#include "time_edit.h"
#include "alarm_edit.h"
#include "alarm.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
RTC_TimeTypeDef alarmTime = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  uint8_t select = 0;//0调整小时，1调整分钟，2调整秒
  uint8_t mode = 0; // 0表示调整RTC，1表示调整闹钟
  
  alarmTime.Hours = 7;//需要设成全局变量供其他文件使用（extern）
  alarmTime.Minutes = 30;
  alarmTime.Seconds = 0;
  RTC_TimeTypeDef now = {0};
  char buf[20];
  
  now.Hours = 23;
  now.Minutes = 59;
  now.Seconds = 50;

  HAL_RTC_SetTime(&hrtc, &now, RTC_FORMAT_BIN);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_RTC_GetTime(&hrtc, &now, RTC_FORMAT_BIN);
    Alarm_Check(now, alarmTime);
    
    
    uint8_t key = Key_GetNum();
    if (Alarm_IsOn() && key != 0) // 如果闹钟响起且有按键被按下
    {
        Alarm_Stop(); // 停止闹钟
    }

    else if (key == 4) // 如果按键值为 4，表示长按
    {
      mode = (mode + 1) % 2; // 切换模式：0 -> 1 -> 0
      
    }

    else if (key == 1)
    {
      select = (select + 1) % 3; // 循环选择调整的时间部分（小时、分钟、秒）
    }
    else if (key == 2)
    {
      if (mode == 0)
        Time_Adjust(select, key);
      else
        Alarm_Adjust(select, key);
    }
    else if (key == 3)
    {
      if (mode == 0)
        Time_Adjust(select, key);
      else
        Alarm_Adjust(select, key);    
      
    }
    
      
    HAL_RTC_GetTime(&hrtc, &now, RTC_FORMAT_BIN);

    sprintf(buf, "%02d:%02d:%02d",
                      now.Hours, now.Minutes, now.Seconds);
    //sprintf 是 C 语言标准库中用于格式化字符串的函数
    OLED_ShowString(2, 1, buf);
    
    if (mode == 0)
      OLED_ShowString(1, 1, "SET TIME");
    else
      OLED_ShowString(1, 1, "SET ALARM ");
    sprintf(buf, "%02d:%02d:%02d",
                      alarmTime.Hours, alarmTime.Minutes, alarmTime.Seconds);
    
    if (Alarm_IsOn())
    {
      if(HAL_GetTick() % 1000 < 500) // 每500ms闪烁一次
        OLED_ShowString(3, 1, buf);
      else
        OLED_ShowString(3, 1, "          ");  
      OLED_ShowString(4, 1, "ALARM!!!");
    }
    else 
    {
      OLED_ShowString(3, 1, buf);
      if (select == 0)
      OLED_ShowString(4, 1, "SET HOUR  ");
      else if (select == 1)
      OLED_ShowString(4, 1, "SET MIN   ");
      else
      OLED_ShowString(4, 1, "SET SEC   ");
    }
    

    HAL_Delay(50);// 如果延时1000ms，STM32 每秒才检查一次按键，短按可能检测不到。改成50ms后，按键响应会好很多
    

  }
  
      
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
