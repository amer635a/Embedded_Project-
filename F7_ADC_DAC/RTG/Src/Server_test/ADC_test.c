#include "RTG.h"
#include "tests.h"

/**
  * @brief   test ADC if can convert analog to digital using ground .
  * @note   can add multiple tests for test ADC.
  *
  */
void analog_to_digital_converter_test(result_test*result )
{
	uint32_t adcVal1;

	 //	Enable ADC and start ADC conversion
	 HAL_ADC_Start(ADC_1);
	 //	Wait for ADC conversion to be completed
	 HAL_ADC_PollForConversion(ADC_1, 10);

	 //	Get ADC value from ADC data register
	  adcVal1 = HAL_ADC_GetValue(ADC_1);


	  // check ADC value
	if( MIN_EXPECTED_ADC<= adcVal1 && adcVal1 <= MAX_EXPECTED_ADC )
	{
		//true case
		result->bool_test=TRUE;
		memcpy(result->msg , STR_SUCCESS,  strlen(STR_SUCCESS)+1 );
		return;
	}
	else
	{
		//false case
		result->bool_test=FALSE;
	    memcpy(result->msg , STR_ADC_FAIL,  strlen(STR_ADC_FAIL)+1);
	    return;
	}

}


/**
  * @brief function for run ADC tests.
  * @note   can add multiple tests for test ADC.
  *         Save the result on result variable
  */
void ADC_tests( result_test*result)
{
	 analog_to_digital_converter_test(result);
}
