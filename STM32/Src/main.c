/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "et_stm32f_arm_kit_lcd.h"
#include <string.h>
#include <stdlib.h>
#define LED_COUNT		64
#define LED_BUFFER_SIZE		24*LED_COUNT+84	// Buffer size needs to be the number of LEDs times 24 bits plus 42 trailing bit to signify the end of the data being transmitted.
uint16_t led_buffer[LED_BUFFER_SIZE] = {0};
uint16_t tact_sw[64]={0};

#define PWM_HIGH_WIDTH		17					// Duty cycle of pwm signal for a logical 1 to be read by the ws2812 chip. Duty cycle = PWM_HIGH_WIDTH/TIM_PERIOD*100
#define PWM_LOW_WIDTH		9					// Duty cycle of pwm signal for a logical 0 to be read by the ws2812 chip. Duty cycle = PWM_LOW_WIDTH/TIM_PERIOD*100
	
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
DMA_HandleTypeDef hdma_tim3_ch4_up;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void rgb(int r,int g,int b)
{
tact_sw[0]=g; //G Channel
tact_sw[1]=r; //R Channel
tact_sw[2]=b; //B Channel	
}
int yay[5];
void pushToUART(int r,int g,int b,int state, int random){
	char send_data[20];
	sprintf(send_data,"[%d,%d,%d,%d,%d]\n",r,g,b,state,random);
	//HAL_UART_Transmit(&huart3,(uint8_t *) send_data,strlen(send_data),100);	
}
void pushColorToUART(int r,int g,int b){
	char send_data[20];
	sprintf(send_data,"[%d,%d,%d,%d,%d]\n",r,g,b,yay[3],yay[4]);
	//HAL_UART_Transmit(&huart3,(uint8_t *) send_data,strlen(send_data),100);	
}


/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
uint16_t posX, posY;
	char pos[50];
	int check = 1;
		char str[20];
	char outBuffer[100];
	char* ptr[5];
	int yay[5];
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */

	LCD_Setup();
	LCD_Clear(Black);
	//write full circle 16 color 6x3
	//row 1
	LCD_SetBackColor(0xf206);
	LCD_DrawFullCircle(28, 292, 24);
	
	LCD_SetBackColor(0xe8ec);
	LCD_DrawFullCircle(28, 240, 24);
	
	LCD_SetBackColor(0x9936);
	LCD_DrawFullCircle(28, 188, 24);
	
	LCD_SetBackColor(0x61d6);
	LCD_DrawFullCircle(28, 136, 24);
	
	LCD_SetBackColor(0x3a96);
	LCD_DrawFullCircle(28, 84, 24);
	
	LCD_SetBackColor(0x24be);
	LCD_DrawFullCircle(28, 32, 24);
	
	//row 2
	LCD_SetBackColor(0x055e);
	LCD_DrawFullCircle(80, 292, 24);
	
	LCD_SetBackColor(0x05fa);
	LCD_DrawFullCircle(80, 240, 24);
	
	LCD_SetBackColor(0x04b1);
	LCD_DrawFullCircle(80, 188, 24);
	
	LCD_SetBackColor(0x4d6a);
	LCD_DrawFullCircle(80, 136, 24);
	
	LCD_SetBackColor(0x8e09);
	LCD_DrawFullCircle(80, 84, 24);
	
	LCD_SetBackColor(0xcee7);
	LCD_DrawFullCircle(80, 32, 24);
	
	//row 3
	LCD_SetBackColor(0xff47);
	LCD_DrawFullCircle(132, 292, 24);
	
	LCD_SetBackColor(0xfe00);
	LCD_DrawFullCircle(132, 240, 24);
	
	LCD_SetBackColor(0xfcc0);
	LCD_DrawFullCircle(132, 188, 24);
	
	LCD_SetBackColor(0xfaa4);
	LCD_DrawFullCircle(132, 136, 24);
	
	LCD_SetBackColor(0x7aa9);
	LCD_DrawFullCircle(132, 84, 24);
	
	LCD_SetBackColor(0x63f1);
	LCD_DrawFullCircle(132, 32, 24);
	
	
	
	HAL_TIM_Base_Start_IT (&htim4);
	
	
	HAL_TIM_Base_Start_IT (&htim1);//count
	


		
		
		
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_4, (uint32_t*) led_buffer, LED_BUFFER_SIZE);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	//check touchscreen row 1
	
  while (1)
  {
	//check touchscreen row 1
		posX = TCS_Read_X();
		posY = TCS_Read_Y();
		
		if(posX >= 266 && posX <= 314 && posY >= 4 && posY <= 48){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(28, 292, 24);
			LCD_SetBackColor(0xf206);
			LCD_DrawFullCircle(28, 292, 24);
			rgb(244, 67, 54);
			pushColorToUART(244, 67, 54);
		}else if(posX >= 214 && posX <= 262 && posY >= 4 && posY <= 48){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(28, 240, 24);
			LCD_SetBackColor(0xe8ec);
			LCD_DrawFullCircle(28, 240, 24);
			rgb(233, 30, 99);
			pushColorToUART(233, 30, 99);
		}else if(posX >= 162 && posX <= 210 && posY >= 4 && posY <= 48){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(28, 188, 24);
			LCD_SetBackColor(0x9936);
			LCD_DrawFullCircle(28, 188, 24);
			rgb(156, 39, 176);
			pushColorToUART(156, 39, 176);
		}else if(posX >= 110 && posX <= 158 && posY >= 4 && posY <= 48){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(28, 136, 24);
			LCD_SetBackColor(0x61d6);
			LCD_DrawFullCircle(28, 136, 24);
			rgb(103, 58, 183);
			pushColorToUART(103, 58, 183);
		}else if(posX >= 58 && posX <= 106 && posY >= 4 && posY <= 48){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(28, 84, 24);
			LCD_SetBackColor(0x3a96);
			LCD_DrawFullCircle(28, 84, 24);
			rgb(63, 81, 181);
			pushColorToUART(63, 81, 181);
			
		}else if(posX >= 4 && posX <= 52 && posY >= 4 && posY <= 48){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(28, 32, 24);
			LCD_SetBackColor(0x24be);
			LCD_DrawFullCircle(28, 32, 24);
			rgb(33, 150, 243);
			pushColorToUART(33, 150, 243);
		}
		
		//check touchscreen row 2
		
		posX = TCS_Read_X();
		posY = TCS_Read_Y();
		
		if(posX >= 266 && posX <= 314 && posY >= 56 && posY <= 104){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(80, 292, 24);
			LCD_SetBackColor(0x055e);
			LCD_DrawFullCircle(80, 292, 24);
			rgb(3, 169, 244);
			pushColorToUART(3, 169, 244);
		}else if(posX >= 214 && posX <= 262 && posY >= 56 && posY <= 104){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(80, 240, 24);
			LCD_SetBackColor(0x05fa);
			LCD_DrawFullCircle(80, 240, 24);
			rgb(0, 188, 212);
			pushColorToUART(0, 188, 212);
		}else if(posX >= 162 && posX <= 210 && posY >= 56 && posY <= 104){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(80, 188, 24);
			LCD_SetBackColor(0x04b1);
			LCD_DrawFullCircle(80, 188, 24);
			rgb(0, 150, 136);
			pushColorToUART(0, 150, 136);
		}else if(posX >= 110 && posX <= 158 && posY >= 56 && posY <= 104){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(80, 136, 24);
			LCD_SetBackColor(0x4d6a);
			LCD_DrawFullCircle(80, 136, 24);
			rgb(76, 175, 80);
			pushColorToUART(76, 175, 80);
		}else if(posX >= 58 && posX <= 106 && posY >= 56 && posY <= 104){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(80, 84, 24);
			LCD_SetBackColor(0x8e09);
			LCD_DrawFullCircle(80, 84, 24);
			rgb(139, 195, 74);
			pushColorToUART(139, 195, 74);
		}else if(posX >= 4 && posX <= 52 && posY >= 56 && posY <= 104){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(80, 32, 24);
			LCD_SetBackColor(0xcee7);
			LCD_DrawFullCircle(80, 32, 24);
			rgb(205, 220, 57);
			pushColorToUART(205, 220, 57);
		}
		
		posX = TCS_Read_X();
		posY = TCS_Read_Y();
		
	//check touchscreen row 3

		if(posX >= 266 && posX <= 314 && posY >= 108 && posY <= 156){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(132, 292, 24);
			LCD_SetBackColor(0xff47);
			LCD_DrawFullCircle(132, 292, 24);
			rgb(255, 235, 59);
			pushColorToUART(255, 235, 59);
		}else if(posX >= 214 && posX <= 262 && posY >= 108 && posY <= 156){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(132, 240, 24);
			LCD_SetBackColor(0xfe00);
			LCD_DrawFullCircle(132, 240, 24);
			rgb(255, 193, 7);
			pushColorToUART(255, 193, 7);
		}else if(posX >= 162 && posX <= 210 && posY >= 108 && posY <= 156){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(132, 188, 24);
			LCD_SetBackColor(0xfcc0);
			LCD_DrawFullCircle(132, 188, 24);
			rgb(255, 152, 0);
			pushColorToUART(255, 152, 0);
			
		}else if(posX >= 110 && posX <= 158 && posY >= 108 && posY <= 156){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(132, 136, 24);
			LCD_SetBackColor(0xfaa4);
			LCD_DrawFullCircle(132, 136, 24);
			rgb(255, 87, 34);
			pushColorToUART(255, 87, 34);
		}else if(posX >= 58 && posX <= 106 && posY >= 108 && posY <= 156){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(132, 84, 24);
			LCD_SetBackColor(0x7aa9);
			LCD_DrawFullCircle(132, 84, 24);
			rgb(121, 85, 72);
			pushColorToUART(121, 85, 72);
		}else if(posX >= 4 && posX <= 52 && posY >= 108 && posY <= 156){
			LCD_SetBackColor(Black);
			LCD_DrawFullCircle(132, 32, 24);
			LCD_SetBackColor(0x63f1);
			LCD_DrawFullCircle(132, 32, 24);
			rgb(96, 125, 139);
			pushColorToUART(96,125,139);
		}
		
		LCD_SetTextColor(Green);
		LCD_DisplayStringLine(Line7, "xxxxxTurnON/OFFxxxxx");
		LCD_SetTextColor(Yellow);
		LCD_DisplayStringLine(Line8, "xxxxxxxRAINBOWxxxxxx");
	
		
		
		
		while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)== RESET){}
		HAL_UART_Receive(&huart1, (uint8_t*) &str, 19, 30);		
		//HAL_UART_Transmit(&huart2,(uint8_t *) str,19,100);
		//String to array
		str[strlen(str) - 1] = '\0'; 
		 ptr[0] = strtok(&str[1], ","); 
		 if (ptr[0] != NULL) { 
			int i = 1; 
			while (ptr[i - 1] != NULL) { 
			 ptr[i] = strtok(NULL, ","); 
			 i++; 
			} 
		 } 
		 
		for (int i = 0; i < 5; i++) { 
			yay[i] = atoi(ptr[i]);
		} 
		 sprintf(outBuffer,"R:%d G:%d B:%d St:%d Rb:%d\n\r",yay[0],yay[1],yay[2],yay[3],yay[4]);
		//rgb(yay[0], yay[1], yay[2]);
		 
		HAL_UART_Transmit(&huart2,(uint8_t *) outBuffer,strlen(outBuffer),100);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Configure the Systick interrupt time 
    */
  __HAL_RCC_PLLI2S_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI3 init function */
static void MX_SPI3_Init(void)
{

  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 72-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 3-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 30-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim3);

}

/* TIM4 init function */
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 72-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE3 PE4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PE5 PE6 PE7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
