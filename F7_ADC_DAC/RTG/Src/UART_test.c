#include "RTG.h"




int test_transmit_receive_data(){
	printf("\r\ntest_transmit_receive_data\r\n");
	HAL_UART_Transmit(UART_4, data_buff_transmint, SIZEOF_DATA_BUFF, TIMEOUT_TIME_100);

	HAL_Delay(100);
	if(receivere_UART5_flag_RxCpltCallback==TRUE)
	{
		HAL_UART_Receive_IT(UART_5, data_buff_receivere, SIZEOF_DATA_BUFF);
		HAL_UART_Transmit(UART_DEBUG, data_buff_receivere, SIZEOF_DATA_BUFF, TIMEOUT_TIME_100);
		printf("\r\n hi hi hi\r\n");
		receivere_UART5_flag_RxCpltCallback = FALSE;
	}

	return TRUE;
}


int UART_tests(int data)
{
	printf("\r\n*** **** ****\r\n");
	HAL_UART_Transmit(UART_DEBUG, "start initialization", 21, TIMEOUT_TIME_100);
	initialization_UART();

	return test_transmit_receive_data();

};
