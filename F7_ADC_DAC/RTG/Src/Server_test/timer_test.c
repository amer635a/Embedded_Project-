
#include "RTG.h"
#include "tests.h"

//check is the timer work good
void timer_test( result_test*result)
{

	//init PSC_counter
	int PSC_counter=PSC_COUNTER_INIT;

	while (1)
	{
		if(time_flag_PeriodElapsedCallback==TRUE)
		{
			PSC_counter--;
			time_flag_PeriodElapsedCallback=FALSE;

			if(PSC_counter==0)
				break;
		}
	}

	//check how many Period elapsed
	 if(PeriodElapsedCallback_couter==PSC_counter_expected)
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

