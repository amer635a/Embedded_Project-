
#include "stm32f7xx_hal.h"
#include "RTG.h"

//Data for TRANSMINT

uint8_t receivere_UART5_flag_RxCpltCallback=FALSE;
uint8_t receivere_UART4_flag_RxCpltCallback=FALSE;


uint8_t flag_R_Master=FALSE;
uint8_t	flag_R_slave=FALSE;

uint8_t flag_ADC_ConvCpltCallback=FALSE;

 uint8_t time_flag_PeriodElapsedCallback=FALSE;


/**
  * @brief This function is called when *any* UART completes receiving X bytes.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==UART_5)
		receivere_UART5_flag_RxCpltCallback = TRUE;
	if(huart==UART_4)
		receivere_UART4_flag_RxCpltCallback = TRUE;
}


void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	flag_R_slave=TRUE;
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	flag_R_Master=TRUE;

 }

// ADC interrupt Callback (convert data finish)
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	flag_ADC_ConvCpltCallback = TRUE;
}


// == Timer Callback ======================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	time_flag_PeriodElapsedCallback=TRUE;

}



