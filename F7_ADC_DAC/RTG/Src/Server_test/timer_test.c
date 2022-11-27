
#include "RTG.h"
#include "tests.h"

void timer_test( result_test*result)
{

int counter=0;
	HAL_TIM_Base_Start_IT(TIM_2); //Initiate timer 2
int new_TIM_counter,old_TIM_counter;
	while (1)
	{
		if(time_flag_PeriodElapsedCallback==TRUE)
		{
			printf("\r\n counter-> %d \r\n",counter);
			time_flag_PeriodElapsedCallback=FALSE;
		}

		new_TIM_counter = __HAL_TIM_GET_COUNTER(TIM_2); //Get the TIM3 Counter Register value on runtime
		if (new_TIM_counter < old_TIM_counter) //Check if period looped
		{
			counter=0;
		}
		counter++;
		old_TIM_counter = new_TIM_counter; //save old counter
	}



	result->bool_test=TRUE;
	memcpy(result->msg , "Success",  8);


}
