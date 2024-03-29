/**
  ******************************************************************************
  * @file    stm32l4xx_hal_msp_template.c
  * @author  MCD Application Team
  * @version V1.7.1
  * @date    21-April-2017
  * @brief   HAL MSP module.
  *          This file template is located in the HAL folder and should be copied 
  *          to the user folder.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#include "stm32l4xx_hal.h"

/** @addtogroup STM32L4xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP HAL MSP module driver
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */ 
}

/**
  * @brief  DeInitialize the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */
}

/**
  * @brief  Initialize the PPP MSP.
  * @param  None
  * @retval None
  */
void HAL_PPP_MspInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */ 
}

/**
  * @brief  DeInitialize the PPP MSP.
  * @param  None  
  * @retval None
  */
void HAL_PPP_MspDeInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */
}

/**
  * @brief TIM MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param htim: TIM handle pointer
  * @retval None
  */


void HAL_TIM_Base_MspInit (TIM_HandleTypeDef *htim)
{

}



void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{ 


}

//PWM stuff abhishek added (Delte if broken)
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{	
  GPIO_InitTypeDef   GPIO_InitStruct;

  //__HAL_RCC_TIM4_CLK_ENABLE();

  __HAL_RCC_TIM4_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_adc;
 
  /*##-1- Enable peripherals and GPIO Clocks #################################*/

	/* ADC1 Periph clock enable */
	//__HAL_RCC_ADC1_CLK_ENABLE();
  __HAL_RCC_ADC_CLK_ENABLE();      //NO ADC1, 2 OR 3??
   /* ADC Periph interface clock configuration */
  __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);  //???


	/* Enable DMA2 clock */
  __HAL_RCC_DMA2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  /*##-2- Configure peripheral GPIO ##########################################*/ 
	GPIO_InitStruct.Pin = GPIO_PIN_1; //which pin
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(ADC1_IRQn, 4, 0);
	HAL_NVIC_EnableIRQ(ADC1_IRQn);
	 //deinit it again
		
		


	 
		//##-3- Configure the DMA  
		//RM0351, table 45 & 46 on page 342 shows: ADC mapped to DMA1/channel 1  or to DMA2/channel 3.
	hdma_adc.Instance                 = DMA2_Channel3; //
	hdma_adc.Init.Request             = DMA_REQUEST_0; //use adc1
	hdma_adc.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	hdma_adc.Init.PeriphInc           = DMA_PINC_DISABLE;
	hdma_adc.Init.MemInc              = DMA_MINC_ENABLE;
	hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma_adc.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
	hdma_adc.Init.Mode                = DMA_CIRCULAR;
	hdma_adc.Init.Priority            = DMA_PRIORITY_MEDIUM;

	//Deinitialize & initintialize the dma for new transfer
	HAL_DMA_DeInit(&hdma_adc);
  HAL_DMA_Init(&hdma_adc);

	__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

		//##-4- Configure the NVIC for DMA 
	HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
	//__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

}
  
/**
  * @brief ADC MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  static DMA_HandleTypeDef  hdma_adc;
  
  /*##-1- Reset peripherals ##################################################*/
   __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
	/* ADC Periph clock disable
   (automatically reset all ADC's) */
  __HAL_RCC_ADC_CLK_DISABLE();
	
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

  //HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

}


 
 
 
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
