
#include "RTG.h"

int test_analog_to_digital(){
	printf("start test_analog_to_digital");
	if (adc_flag){

		printf("DAC value=%d >> ADC value =%ld \n\r", DEFAULT_TRANSMIT_NUMBER,
		HAL_ADC_GetValue(ADC_1)); //Sample the DAC value using the ADC
		adc_flag = FALSE;
	}

	return TRUE  ;
}


int DAC_ADC_tests(int data){


	printf("start DAC ADC initialization");
	initialization_DAC(data);

	return test_analog_to_digital();

};
