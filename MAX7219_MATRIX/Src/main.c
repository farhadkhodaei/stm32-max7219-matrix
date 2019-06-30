/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MAX7219_Matrix.h"
#include "MAX7219.h"


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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
const uint64_t symbol[] = {
	0x1800183860663c00,
	0x10387cfefeee4400,
	0x060e0c0808281800,
	0x10307efe7e301000,
	0x1018fcfefc181000
};

const uint64_t numbers[] = {
	/* 8     =>      1   row */
	0x3c66666e76663c00, /* 0 */
	0x7e1818181c181800,	/* 1 */
	0x7e060c3060663c00,	/* 2 */
	0x3c66603860663c00,	/* 3 */
	0x30307e3234383000, /* 4 */
	0x3c6660603e067e00, /* 5 */
	0x3c66663e06663c00, /* 6 */
	0x1818183030667e00, /* 7 */
	0x3c66663c66663c00, /* 8 */
	0x3c66607c66663c00, /* 9 */
};

const uint64_t Atoz[] = {
	0x6666667e66663c00, /* A */
	0x3e66663e66663e00,	/* B */
	0x3c66060606663c00,
	0x3e66666666663e00,
	0x7e06063e06067e00,
	0x0606063e06067e00,
	0x3c66760606663c00,
	0x6666667e66666600,
	0x3c18181818183c00,
	0x1c36363030307800,
	0x66361e0e1e366600,
	0x7e06060606060600,
	0xc6c6c6d6feeec600,
	0xc6c6e6f6decec600,
	0x3c66666666663c00,
	0x06063e6666663e00,
	0x603c766666663c00,
	0x66361e3e66663e00,
	0x3c66603c06663c00,
	0x18181818185a7e00,
	0x7c66666666666600,
	0x183c666666666600,
	0xc6eefed6c6c6c600,
	0xc6c66c386cc6c600,
	0x1818183c66666600,
	0x7e060c1830607e00,
	0x0000000000000000,
	0x7c667c603c000000,
	0x3e66663e06060600,
	0x3c6606663c000000,
	0x7c66667c60606000,
	0x3c067e663c000000,
	0x0c0c3e0c0c6c3800,
	0x3c607c66667c0000,
	0x6666663e06060600,
	0x3c18181800180000,
	0x1c36363030003000,
	0x66361e3666060600,
	0x1818181818181800,
	0xd6d6feeec6000000,
	0x6666667e3e000000,
	0x3c6666663c000000,
	0x06063e66663e0000,
	0xf0b03c36363c0000,
	0x060666663e000000,
	0x3e403c027c000000,
	0x1818187e18180000,
	0x7c66666666000000,
	0x183c666600000000,
	0x7cd6d6d6c6000000,
	0x663c183c66000000,
	0x3c607c6666000000, /* y */
	0x3c0c18303c000000  /* z */
};
extern uint8_t FrameBuffer[MAX7219_IC_NUM][8];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void change_num_to(unsigned int new_num);

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
  unsigned int num = 0;
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	MAX7219_MatrixInit();
	MAX7219_MatrixSetRow64(3, numbers[0]);			
	MAX7219_MatrixSetRow64(2, numbers[0]);		
	MAX7219_MatrixSetRow64(1, numbers[0]);		
	MAX7219_MatrixSetRow64(0, numbers[0]);		
	MAX7219_MatrixUpdate();			
	HAL_Delay(200);
  while (1)
  {
		/*MAX7219_MatrixSetRow64(3, symbol[0]);
		MAX7219_MatrixSetRow64(2, symbol[0]);
		MAX7219_MatrixSetRow64(1, symbol[0]);
		MAX7219_MatrixSetRow64(0, symbol[0]);		
		MAX7219_MatrixUpdate();		
		HAL_Delay(5000);
			*/			
		
		
		
		
		change_num_to(num++);	
		GPIOA->ODR ^= 1<<4;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA3 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void change_num_to(unsigned int new_num)
{
	static unsigned int prev_num;
	unsigned int dl0, dl1, dl2, dl3, dn0, dn1, dn2, dn3, i, k;
	dl0 = prev_num - (prev_num / 10)*10;
	dl1 = prev_num /10 - (prev_num / 100)*10;
	dl2 = prev_num /100 - (prev_num / 1000)*10;
	dl3 = prev_num /1000 - (prev_num / 10000)*10;
	
	dn0 = new_num - (new_num / 10)*10;
	dn1 = new_num /10 - (new_num / 100)*10;
	dn2 = new_num /100 - (new_num / 1000)*10;
	dn3 = new_num /1000 - (new_num / 10000)*10;
	for (k=0;k<8;k++)
	{
			for (i=7;i>=1;i--)
			{
				if (dn0 != dl0)
				{
					FrameBuffer[0][i] = FrameBuffer[0][i-1];
				}
				if (dn1 != dl1)
				{
					FrameBuffer[1][i] = FrameBuffer[1][i-1];
				}
				if (dn2 != dl2)
				{
					FrameBuffer[2][i] = FrameBuffer[2][i-1];
				}
				if (dn3 != dl3)
				{
					FrameBuffer[3][i] = FrameBuffer[3][i-1];
				}
			}
			if (dn0 != dl0)
			{
				FrameBuffer[0][0] = (numbers[dn0] & (((uint64_t)255)<<(8*k)))>>(8*k);
			}
			if (dn1 != dl1)
			{
				FrameBuffer[1][0] = (numbers[dn1] & (((uint64_t)255)<<(8*k)))>>(8*k);
			}
			if (dn2 != dl2)
			{
				FrameBuffer[2][0] = (numbers[dn2] & (((uint64_t)255)<<(8*k)))>>(8*k);
			}
			if (dn3 != dl3)
			{
				FrameBuffer[3][0] = (numbers[dn3] & (((uint64_t)255)<<(8*k)))>>(8*k);
			}
			
		MAX7219_MatrixUpdate();
		HAL_Delay(125);
	}
	prev_num = new_num;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
