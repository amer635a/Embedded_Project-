#include "RTG.h"




result_test analog_to_digital_converter_test()
{
	result_test result;
	uint32_t adcVal1;
	uint32_t expected_adc_value=0;
	 //	Enable ADC and start ADC conversion
	 HAL_ADC_Start(ADC_1);
	 //	Wait for ADC conversion to be completed
	 HAL_ADC_PollForConversion(ADC_1, 10);

	 //	Get ADC value from ADC data register
	  adcVal1 = HAL_ADC_GetValue(ADC_1);

	if(expected_adc_value-100 < adcVal1 && adcVal1 < expected_adc_value+100 )
	{
		result.bool_test=TRUE;
		memcpy(result.msg , "Success",  8);
	}
	else
	{
		result.bool_test=FALSE;
		memcpy(result.msg , "URT-4, bad receive data",  24);
	}
	return result;
}



void ADC_tests( result_test*result)
{

	HAL_UART_Transmit(UART_DEBUG, "start initialization", 21, TIMEOUT_TIME_100);

	*result=analog_to_digital_converter_test();

}
