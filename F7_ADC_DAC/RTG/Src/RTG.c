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

uint8_t data_from_spi1=0;
uint8_t data_to_spi2=0;

void rtg_main() {
	HAL_SPI_Receive_IT(SPI_2, &data_from_spi1, 1);
	while (1) {
		data_to_spi2++;
		data_to_spi2 %= 255;
		HAL_SPI_Transmit(SPI_1, &data_to_spi2, 1, 100); //master initiates a byte of data to slave with address 44

		switch (data_from_spi1 % 3) {
		case 0:
			// Toggle led 1
			HAL_GPIO_TogglePin(GPIO_PER_1, GPIO_LED_1);
			break;

		case 1:
			// Toggle led 2
			HAL_GPIO_TogglePin(GPIO_PER_1, GPIO_LED_2);
			break;

		case 2:
			// Toggle led 3
			HAL_GPIO_TogglePin(GPIO_PER_1, GPIO_LED_3);
			break;

		default:
			// Error message
			printf("ERROR\r\n");
		}
		printf("We got %d from SPI \n\r", data_from_spi1);
		HAL_Delay(1000);
	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi == SPI_2) {
		HAL_SPI_Receive_IT(SPI_2, &data_from_spi1, 1);
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
