/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
int main(void) {
HAL_Init(); // Reset of all peripherals, init the Flash and Systick
SystemClock_Config(); //Configure the system clock
/* This example uses HAL library calls to control
the GPIOC peripheral. You’ll be redoing this code
with hardware register access. */
	
	
	// LAB 1 Part 1: //
//__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
	
	//RCC:Reset and clock control. AHB: peripheral clock enable register.
	RCC->AHBENR |= 0x80000; //"Bit 19 IOPCEN: I/O port C clock enable". 19th bit position. We know 19th bit from data sheet RM0091 on page 122.
	
	HAL_Delay(2); //Delays 2 milli-sec
	
	GPIOC->MODER |= 0x5000; //setting PC6 & 7. PC6 is connected to RED LED. PC7 is connected to BLUE LED.
	
	GPIOC->OTYPER &= 0x0; //no OR (|) . GPIO port output type register

	GPIOC->OSPEEDR &= 0x0; //GPIO port output speed register to Low speed
	
	GPIOC->PUPDR &= 0x0; //GPIO port pull-up/pull-down register: off
	
	//the following codes are replaced on top ://
//// Set up a configuration struct to pass to the initialization function
//GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_9,
//GPIO_MODE_OUTPUT_PP,
//GPIO_SPEED_FREQ_LOW,
//GPIO_NOPULL};
//HAL_GPIO_Init(GPIOC, &initStr); // Initialize pins PC8 & PC9



//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // Start PC8 high 

// END: "the following codes are replaced on top"//





//Debouncing is removing unwanted input noise from buttons, 
//switches or other user input. Debouncing prevents extra activations 
//or slow functions from triggering too often. Debouncing is used in hardware 
//switches, programs and websites.

uint32_t debouncer = 0;


//For Part 1, the following while loop part must be uncommented: //



////GPIOC->ODR |= 0x80; //Let's enable color RED LED  (red is ON)

//while (1) {
//HAL_Delay(300); // Delay 200ms benween blinks.
//// Toggle the output state of both PC8 and PC9
////HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
////// Toggle the output state of both PC8 and PC9
////HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);

//	if(GPIOC->ODR == 0x80) {// if red is on, 
//	  	GPIOC->ODR = 0x40;
//		  }
//		else{
//			GPIOC->ODR = 0x80;
//		}
//}

// END: "For Part 1, the following while loop part must be uncommented:"//




////////------------------Part 2-----------------------------/////////


//RCC:Reset and clock control. AHB: peripheral clock enable register. Pin PA0


RCC->AHBENR |= 1 << 17; // We know 17th bit from data sheet RM0091 on page 122 that says "Bit 17 IOPBEN: I/O port A clock enable".
//to make 17th bit "1", which will enable it, we do "<<17" which will move 17 digits from right to left and make the 18th digit 1.
//Since the counting starts from "0", 17th bit will be 18th digit when counting from right. 
//"|" is an OR operator. In this case, it will just copy everything as it is and only change
// the 18th digit to "1".

HAL_Delay(2); //Delays 2 milli-sec

GPIOA->MODER &= ~(3 << 0); //setting A0 to input mode. The "3" in decimal is "11" in binary. "7" in decimal is "111" binary.
// 0th moder takes 2 bits. So 11 will make the last 1st 2 digits to 00 because The "~" makes it opposite".
// 

GPIOA->OSPEEDR &= ~(3 << 0); //GPIO port output speed register to Low speed
GPIOA->PUPDR &= ~(3 << 0); //GPIO port pull-up/pull-down register. enable pull down.
GPIOA->PUPDR |= (1 << 1);// shift left 1 digit and make it "1".

GPIOC->ODR |= 1 << 6; // 6th bit = 1. shift 6 digits from right to left and make the next digit 1.
GPIOC->ODR |= ~(1 << 7); 6th bit = 0. //shift 7 digits from right to left and make the next digit 1.then reverse.

while (1){
	
    debouncer = (debouncer << 1); // Always shift every loop iteration. shift right to left one digit.
    if ((GPIOA->IDR & 0x01)) //reads the pull-down resistance. If input is set/high.
    {
        debouncer |= 0x01; //set lowest bit of bit vector
    }
    if (debouncer == 0xFFFFFFFF)
    {
        // This code triggers repeatedly when button is steady high!
    }
    if (debouncer == 0x00000000)
    {
        // This code triggers repeatedly when button is steady low!
    }
    if (debouncer == 0x7FFFFFFF)
    {
        // This code triggers only once when transitioning to steady high!
        GPIOC->ODR ^= 1 << 6; // "^" is XOR 
        GPIOC->ODR ^= 1 << 7;

    }

    HAL_Delay(2);//delay 2ms to avoid errors.

}
	








	
 
//	else{
//		 
//		   debouncer = (debouncer << 1); // Always shift every loop iteration
//		   GPIOC->ODR = 0x80; //red
//		 
//	if(GPIOC->ODR == 0x80) {  
//		   GPIOC->ODR = 0x40;//Pin 7 is ON (Blue)
//	//	a=false;
//		}
//		else {
//				 GPIOC->ODR = 0x80; //GPIO port output data register (ODR6)Pin 6 is ON (red) & PIN 7 is OFF.
//		//	a=true;
//		}
//		
//		}
		//RCC->AHBENR |= 0x0; //disable the 19th bit "C clock"; "reset button"
		
		//GPIOC->ODR = 0x40 ; //GPIO port output data register (ODR6)Pin 6 is ON (red) & PIN 7 is OFF.
		//GPIOA->PUPDR &= 0x0;


//if (debouncer == 0xFFFFFFFF) {
//// This code triggers repeatedly when button is steady high!
//}
//if (debouncer == 0x00000000) {
//// This code triggers repeatedly when button is steady low!
//}
//if (debouncer == 0x7FFFFFFF) {
//// This code triggers only once when transitioning to steady high!
//}
//// When button is bouncing the bit-vector value is random since bits are set when
////the button is high and not when it bounces low.
//	
	
// When button is bouncing the bit-vector value is random since bits are set when
//the button is high and not when it bounces low.	


//HAL_Delay(200); // Delay 200ms
//// Toggle the output state of both PC8 and PC9
//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9);
	
}



		//RCC->AHBENR |= 0x0; //disable the 19th bit "C clock"; "reset button"
		
		//GPIOC->ODR = 0x40 ; //GPIO port output data register (ODR6)Pin 6 is ON (red) & PIN 7 is OFF.
		//GPIOA->PUPDR &= 0x0;





/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

#ifdef  USE_FULL_ASSERT
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