#include "stm32f7xx_hal.h"
#include "RTG.h"

//Data for TRANSMINT

uint8_t receivere_UART5_flag_RxCpltCallback=FALSE;
uint8_t data_buff_transmint[SIZEOF_DATA_BUFF]="*  Hi from URT  *";
uint8_t data_buff_receivere[SIZEOF_DATA_BUFF];

void initialization_UART( )
{
	//Prepare Receive UART to receive data
	HAL_UART_Receive_IT(UART_5, data_buff_receivere, SIZEOF_DATA_BUFF);

}




/**
  * @brief This function is called when *any* UART completes receiving X bytes.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==UART_5)
		receivere_UART5_flag_RxCpltCallback = TRUE;
}
