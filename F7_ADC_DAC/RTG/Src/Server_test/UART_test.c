#include "RTG.h"
#include "tests.h"

//buffer for receivers
uint8_t data_buff_receiver2[SIZEOF_DATA_BUFF];
uint8_t data_buff_receiver1[SIZEOF_DATA_BUFF];


/**
  * @brief test for check transmit data on UART.
  * @param data user data for check.
  * @param lenght size of user data.
  * @param result saving the result of test.
  */

result_test test_transmit_receive_data(const char* data_for_check,uint8_t lenght,result_test*result){

	int waiting_counter=0;

	//Prepare Receive UART to receive data
	HAL_UART_Receive_IT(UART_5, data_buff_receiver1, lenght);
	//Prepare Receive UART to Transmit data
	HAL_UART_Transmit_IT(UART_4, data_for_check, lenght);


	while(1)
	{
		//Callback-UART5 received data
		if(receivere_UART5_flag_RxCpltCallback==TRUE)
		{
			//check if UART5 received a right data
			if( check_data(data_for_check,data_buff_receiver1,lenght)==FALSE )
			{
				result->bool_test=FALSE;
				memcpy(result->msg , STR_FAIL_UART5_RECEIVE, strlen(STR_FAIL_UART5_RECEIVE)+1);
				return ;
			}

			//Prepare Receive UART to receive data
			HAL_UART_Receive_IT(UART_4, data_buff_receiver2, lenght);
			//Prepare Receive UART to Transmit data
			HAL_UART_Transmit_IT(UART_5, data_buff_receiver1, lenght);

			receivere_UART5_flag_RxCpltCallback = FALSE;
		}
		//Callback-UART4 received data
		if(receivere_UART4_flag_RxCpltCallback==TRUE)
		{

			//check if UART4 received a right data
			if( check_data(data_for_check,data_buff_receiver1,lenght)==FALSE )
			{
				result->bool_test=FALSE;
				memcpy(result->msg , STR_FAIL_UART4_RECEIVE,  strlen(STR_FAIL_UART4_RECEIVE)+1);
				return  ;
			}
			receivere_UART4_flag_RxCpltCallback= FALSE;
			break;
		}

		HAL_Delay(10);
		//check if its not taking long time to finish
		if((++waiting_counter) > MAX_WAITING_COUNTER)
		{
			result->bool_test=FALSE;
			memcpy(result->msg , STR_FAIL_TIMEOUT,  strlen(STR_FAIL_TIMEOUT)+1 );
			return  ;
		}

	}


	result->bool_test=TRUE;
	memcpy(result->msg , STR_SUCCESS,  strlen(STR_SUCCESS)+1);

}

/**
  * @brief function for run UART tests .
  * @note   can add multiple tests for test UART.
  * @param data_for_check user data for check.
  * @param lenght size of user data.
  * @param result  saving the result of test.
  */

void UART_tests(char* data_for_check,uint8_t lenght ,result_test*result)
{
	  //start transmit and receive data test
	  test_transmit_receive_data(data_for_check,lenght,result);

}
