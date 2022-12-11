
#include "RTG.h"
#include "tests.h"


/**
  * @brief check is the timer work good
  * @param result saving the result of test.
  */
void timer_test( result_test*result)
{
	//start timer 2 -> (0.5 second)
	HAL_TIM_Base_Start_IT(TIM_2);

	//delay for 1 second
	HAL_Delay(ONE_SEC_DEALY_TIMER);


	//check how many Period elapsed
	 if(PeriodElapsedCallback_couter_timer2==PSC_COUNTER_2)
	 {
		 result->bool_test=TRUE;
		 memcpy(result->msg , STR_SUCCESS,  strlen(STR_SUCCESS)+1);
	 }
	 else
	 {
		 result->bool_test=FALSE;
		 memcpy(result->msg , STR_FAIL_TIMER,  strlen(STR_FAIL_TIMER)+1);

	 }
}

