#include "RTG.h"



uint8_t data_buff_receiver_Master_SPI[SIZEOF_DATA_BUFF];
uint8_t data_buff_receiver1_Slave_SPI[SIZEOF_DATA_BUFF];





result_test test_transmit_receive_data_SPI(const char* data,uint8_t lenght)
{
	result_test result;
	int waiting_counter=0;
	while (1)
	{

		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data,
				data_buff_receiver_Master_SPI, lenght);
		HAL_Delay(100);
		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, "",
				data_buff_receiver_Master_SPI, lenght);
		HAL_Delay(100);
		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, data_buff_receiver1_Slave_SPI,
						data_buff_receiver1_Slave_SPI, lenght);
		HAL_Delay(100);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data_buff_receiver_Master_SPI,
						data_buff_receiver_Master_SPI, lenght);



		HAL_Delay(10);
		if((++waiting_counter) > MAX_WAITING_COUNTER)
		{
			result.bool_test=FALSE;
			memcpy(result.msg , "bad conotion between UART",  26);
			return result;
		}

	}

	result.bool_test=TRUE;
	memcpy(result.msg , "Success",  8);
	return result;
}


void SPI_tests(char* data,uint8_t lenght,uint8_t iterations,result_test*result)
{
	data_buff_receiver_Master_SPI[SIZEOF_DATA_BUFF]=0;
	data_buff_receiver1_Slave_SPI[SIZEOF_DATA_BUFF]=0;

	HAL_UART_Transmit(UART_DEBUG, "start initialization", 21, TIMEOUT_TIME_100);

	*result=test_transmit_receive_data_SPI(data,lenght);

}
