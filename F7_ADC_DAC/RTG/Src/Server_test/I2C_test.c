#include "RTG.h"
#include "tests.h"


uint8_t data_buff_receiver_Master_I2C[SIZEOF_DATA_BUFF];
uint8_t data_buff_receiver1_Slave_I2C[SIZEOF_DATA_BUFF];





result_test test_transmit_receive_data_I2C(const char* data,uint8_t lenght)
{
	result_test result;
	int waiting_counter=0;

	HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, &data_buff_receiver1_Slave_I2C, lenght);
	HAL_I2C_Master_Transmit_DMA(I2C_MASTER, 44, data, lenght);

	while (1)
	{
		if(flag_R_slave==TRUE)
		{

			if( check_data(data,data_buff_receiver1_Slave_I2C,lenght)==FALSE )
			{
				result.bool_test=FALSE;
				memcpy(result.msg , STR_FAIL_SLAVE_RECEIVE,  strlen(STR_FAIL_SLAVE_RECEIVE)+1);
				return result;
			}


			HAL_I2C_Master_Receive_DMA(I2C_MASTER,44, &data_buff_receiver_Master_I2C, lenght);
			HAL_I2C_Slave_Transmit_DMA(I2C_SLAVE,data_buff_receiver1_Slave_I2C, lenght);
			flag_R_slave=FALSE;
		}
		if(flag_R_Master==TRUE)
		{
			if( check_data(data,data_buff_receiver_Master_I2C,lenght)==FALSE )
			{
				result.bool_test=FALSE;
				memcpy(result.msg , STR_FAIL_MASTER_RECEIVE,  strlen(STR_FAIL_MASTER_RECEIVE)+1);
				return result;
			}
			HAL_GPIO_TogglePin(GPIO_PER_1, GPIO_LED_2);
			flag_R_Master=FALSE;
			break;
		}

		HAL_Delay(10);
		if((++waiting_counter) > MAX_WAITING_COUNTER)
		{
			result.bool_test=FALSE;
			memcpy(result.msg , STR_FAIL_TIMEOUT,  strlen(STR_FAIL_TIMEOUT)+1);
			return result;
		}

	}

	result.bool_test=TRUE;
	memcpy(result.msg , STR_SUCCESS,  strlen(STR_SUCCESS)+1);
	return result;
}


void I2C_tests(char* data,uint8_t lenght,uint8_t iterations,result_test*result)
{
	data_buff_receiver_Master_I2C[SIZEOF_DATA_BUFF]=0;
	data_buff_receiver1_Slave_I2C[SIZEOF_DATA_BUFF]=0;


	*result=test_transmit_receive_data_I2C(data,lenght);

}
