#include "RTG.h"
#include "tests.h"



uint8_t data_buff_receiver_Master_SPI[SIZEOF_DATA_BUFF]={0};
uint8_t data_buff_receiver1_Slave_SPI[SIZEOF_DATA_BUFF]={0};




/**
  * @brief test for check transmit data on SPI protocol
  * @param data user data for check.
  * @param lenght size of user data.
  * @param result saving the result of test.
  */
void test_transmit_receive_data_SPI(const char* data,uint8_t lenght,result_test*result)
{

	uint8_t waiting_counter=0;
	while (1)
	{

		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, data_buff_receiver1_Slave_SPI,
				data_buff_receiver1_Slave_SPI, lenght);
		HAL_Delay(100);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data,
				data_buff_receiver_Master_SPI, lenght);
		HAL_Delay(100);

		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, data_buff_receiver1_Slave_SPI,
						data_buff_receiver1_Slave_SPI, lenght);
		HAL_Delay(100);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data_buff_receiver_Master_SPI,
						data_buff_receiver_Master_SPI, lenght);

		//check if implicit received a right data
		if( check_data(data,data_buff_receiver_Master_SPI,lenght)==FALSE )
		{
			result->bool_test=FALSE;
			memcpy(result->msg , STR_FAIL_MASTER_RECEIVE,  strlen(STR_FAIL_MASTER_RECEIVE)+1);
			return ;
		}
		else
			break;


		//check if its not taking long time to finish
		if((++waiting_counter) > MAX_WAITING_COUNTER)
		{
			result->bool_test=FALSE;
			memcpy(result->msg , STR_FAIL_TIMEOUT,  strlen(STR_FAIL_TIMEOUT)+1);
			return ;
		}
	}

   result->bool_test=TRUE;
   memcpy(result->msg , STR_SUCCESS,  strlen(STR_SUCCESS)+1);

}

/**
  * @brief function for run SPI tests.
  * @note   can add multiple tests for test SPI.
  * @param data_for_check user data for check.
  * @param lenght size of user data.
  * @param result  saving the result of tests.
  */

void SPI_tests(char* data,uint8_t lenght,uint8_t iterations,result_test*result)
{
	test_transmit_receive_data_SPI(data,lenght,result);
}
