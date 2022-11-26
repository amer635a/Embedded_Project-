
#include "stm32f7xx_hal.h"
#include "RTG.h"

int adc_flag=FALSE;

void initialization_DAC(int transmit_number)
{
	//Sets the DAC output according to num (0-4k)
	HAL_DAC_SetValue(DAC_1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, transmit_number);

	//Enables DAC conversion
	HAL_DAC_Start(DAC_1, DAC_CHANNEL_1);
}


// ADC interrupt Callback (convert data finish)
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	adc_flag = TRUE;
}
