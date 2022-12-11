#include "RTG.h"
#include "tests.h"


uint8_t data_buff_receiver_Master_I2C[SIZEOF_DATA_BUFF];
uint8_t data_buff_receiver1_Slave_I2C[SIZEOF_DATA_BUFF];


/**
  * @brief test for check transmit data on I2C protocol.
  * @param data user data for check.
  * @param lenght size of user data.
  * @param result saving the result of test.
  */

void test_transmit_receive_data_I2C(const char* data,uint8_t lenght,result_test*result)
{

	uint8_t waiting_counter=0;

	//Prepare Receive salve to receive data
	HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, &data_buff_receiver1_Slave_I2C, lenght);
	//Prepare Transmit master to receive data
	HAL_I2C_Master_Transmit_DMA(I2C_MASTER, SLAVE_ADRESS_I2C1, data, lenght);

	while (1)
	{
		//slave received data
		if(flag_R_slave==TRUE)
		{
				//check if implicit received a right data
			if( check_data(data,data_buff_receiver1_Slave_I2C,lenght)==FALSE )
			{
				result->bool_test=FALSE;
				memcpy(result->msg , STR_FAIL_SLAVE_RECEIVE,  strlen(STR_FAIL_SLAVE_RECEIVE)+1);
				return;
			}

			//Prepare Receive master to receive data
			HAL_I2C_Master_Receive_DMA(I2C_MASTER,SLAVE_ADRESS_I2C1, &data_buff_receiver_Master_I2C, lenght);
			//Prepare Transmit Slave to receive data
			HAL_I2C_Slave_Transmit_DMA(I2C_SLAVE,data_buff_receiver1_Slave_I2C, lenght);
			flag_R_slave=FALSE;
		}
		//master received data
		if(flag_R_Master==TRUE)
		{
			//check if implicit received a right data
			if( check_data(data,data_buff_receiver_Master_I2C,lenght)==FALSE )
			{
				result->bool_test=FALSE;
				memcpy(result->msg , STR_FAIL_MASTER_RECEIVE,  strlen(STR_FAIL_MASTER_RECEIVE)+1);
				return ;
			}
			flag_R_Master=FALSE;
			break;
		}

		HAL_Delay(10);
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
	return ;
}

/**
  * @brief function for run I2C tests.
  * @note   can add multiple tests for test I2C.
  * @param data_for_check user data for check.
  * @param lenght size of user data.
  * @param result  saving the result of tests.
  */

void I2C_tests(char* data,uint8_t lenght,result_test*result)
{

	//start transmit and receive data test
	 test_transmit_receive_data_I2C(data,lenght,result);

}
