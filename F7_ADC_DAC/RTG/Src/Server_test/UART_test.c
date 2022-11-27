#include "RTG.h"
#include "tests.h"


uint8_t data_buff_receiver2[SIZEOF_DATA_BUFF];
uint8_t data_buff_receiver1[SIZEOF_DATA_BUFF];



result_test test_transmit_receive_data(const char* data,uint8_t lenght){

	int waiting_counter=0;
	result_test result;
	//Prepare Receive UART to receive data
	HAL_UART_Receive_IT(UART_5, data_buff_receiver1, lenght);
	HAL_UART_Transmit_IT(UART_4, data, lenght);


	while(1)
	{
		if(receivere_UART5_flag_RxCpltCallback==TRUE)
		{
			if( check_data(data,data_buff_receiver1,lenght)==FALSE )
			{
				result.bool_test=FALSE;
				memcpy(result.msg , STR_FAIL_UART5_RECEIVE, strlen(STR_FAIL_UART5_RECEIVE)+1);
				return result;
			}
			HAL_UART_Receive_IT(UART_4, data_buff_receiver2, lenght);
			HAL_UART_Transmit_IT(UART_5, data_buff_receiver1, lenght);

			receivere_UART5_flag_RxCpltCallback = FALSE;
		}

		if(receivere_UART4_flag_RxCpltCallback==TRUE)
		{
			HAL_GPIO_TogglePin(GPIO_PER_1, GPIO_LED_2);

			if( check_data(data,data_buff_receiver1,lenght)==FALSE )
			{
				result.bool_test=FALSE;
				memcpy(result.msg , STR_FAIL_UART4_RECEIVE,  strlen(STR_FAIL_UART4_RECEIVE)+1);
				return result;
			}
			receivere_UART4_flag_RxCpltCallback= FALSE;
			break;
		}

		HAL_Delay(10);
		if((++waiting_counter) > MAX_WAITING_COUNTER)
		{
			result.bool_test=FALSE;
			memcpy(result.msg , STR_FAIL_TIMEOUT,  strlen(STR_FAIL_TIMEOUT)+1 );
			return result;
		}

	}
	printf("\r\n  end \r\n");
	result.bool_test=TRUE;
	memcpy(result.msg , STR_SUCCESS,  strlen(STR_SUCCESS)+1);

	return result;

}


void UART_tests(char* data,uint8_t lenght,uint8_t iterations,result_test*result)
{
	printf("\r\n*** **** ****\r\n");

	HAL_UART_Transmit(UART_DEBUG, "start initialization", 21, TIMEOUT_TIME_100);

	*result=test_transmit_receive_data(data,lenght);

}
