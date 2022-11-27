#include "RTG.h"

/****************************************
 *
 * SPI1
 * PA5 SCK   (CN7)
 * PA6 MISO	 (CN7)
 * PB5 MOSI  (CN7)
 *
 * SPI2
 * PB10 SCK (CN10)
 * PC2 MISO (CN10)
 * PC3 MOSI (CN9)
 *
 **********************************************/

uint8_t data_from_spi1='A';
uint8_t data_to_spi2=0;

uint8_t data_R_master[10]={0};
uint8_t data_R_slave[10]={0};
uint8_t send_data[10]="ameer 665";
uint8_t flag_R_master_SPI=FALSE;
uint8_t flag_R_slave_SPI=FALSE;

void rtg_main()
{
	printf("\r\n * start * \r\n");

	HAL_SPI_Receive_IT(SPI_SLAVE, data_R_slave, 10);
//	HAL_SPI_Receive_IT(SPI_SLAVE, &data_from_spi1, 1);
	HAL_SPI_Transmit(SPI_MASTER,send_data, 10,100 );
	//HAL_SPI_Transmit(SPI_MASTER, &data_to_spi2, 1, 100);
	while (1)
	{
		if(flag_R_slave_SPI==TRUE)
		{
			printf("\r\n flag_R_slave_SPI->%s \r\n",data_R_slave);
			 HAL_SPI_Receive_IT(SPI_MASTER, data_R_master, 10);
			 HAL_SPI_Transmit (SPI_SLAVE,(uint8_t*)"ameer 665", 10,100);
			 SPI_SLAVE.
			flag_R_slave_SPI=FALSE;
		}

		if(flag_R_master_SPI==TRUE)
		{
			printf("\r\n flag_R_master_SPI->%s \r\n ");
			flag_R_master_SPI=FALSE;
		}




	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi == SPI_SLAVE) {
		flag_R_slave_SPI=TRUE;
		HAL_SPI_Receive_IT(SPI_SLAVE, &data_from_spi1, 1);
	}
	if (hspi == SPI_MASTER) {
		flag_R_master_SPI=TRUE;
		}
}
/*
 void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
 void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi);
 */
