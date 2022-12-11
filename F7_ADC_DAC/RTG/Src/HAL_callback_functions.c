
#include "stm32f7xx_hal.h"
#include "RTG.h"

//Data for TRANSMINT

//flags for UART interrput
uint8_t receivere_UART5_flag_RxCpltCallback=FALSE;
uint8_t receivere_UART4_flag_RxCpltCallback=FALSE;

uint8_t receive_SPI_Master_flag_RxCpltCallback=FALSE;
uint8_t receive_SPI_Slave_flag_RxCpltCallback=FALSE;

//flags for I2c interrput
uint8_t flag_R_Master=FALSE;
uint8_t	flag_R_slave=FALSE;

//flags for adc interrput
uint8_t flag_ADC_ConvCpltCallback=FALSE;

uint8_t time_flag_PeriodElapsedCallback=FALSE;

uint32_t PeriodElapsedCallback_couter_timer1=0;
uint32_t PeriodElapsedCallback_couter_timer2=0;

//data of udp
ip_addr_t  addr_global;

u32_t addr_int;
u16_t port_global;
struct pbuf *p_global;
const char* remoteIP_global;
struct pbuf *txBuf;
struct udp_pcb *upcb_global;
u32_t addr_TRY_GOLABL;
/**
  * @brief This function is called when *any* UART completes receiving X bytes.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==UART_5)
		receivere_UART5_flag_RxCpltCallback = TRUE;
	if(huart==UART_4)
		receivere_UART4_flag_RxCpltCallback = TRUE;
}

/**
  * @brief This function is called when Slave I2C completes receiving X bytes.
  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	flag_R_slave=TRUE;
}

/**
  * @brief This function is called when Master I2C completes receiving X bytes.
  */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	flag_R_Master=TRUE;

 }

// ADC interrupt Callback (convert data finish)
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	flag_ADC_ConvCpltCallback = TRUE;
}


// == Timer Callback ======================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==TIM_2)
		++PeriodElapsedCallback_couter_timer2;
}

/**
  * @brief This function is called when udp receive Block.
  */
void udp_receive_callback(
		void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	flag_message_From_client=TRUE;
	/* Get the IP of the Client */
	/* Get the IP of the Client */


	addr_TRY_GOLABL=addr->addr;

    remoteIP_global = ipaddr_ntoa(addr);

	upcb_global=upcb;

	port_global=port;
	p_global=p;

	handleMessageFromClient(p);

}

/**
  * @brief This function is called when any SPI completes receiving X bytes.
  */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {

	if (hspi == SPI_MASTER)
	{
		receive_SPI_Master_flag_RxCpltCallback=TRUE;
	}
	if (hspi == SPI_SLAVE)
	{
		receive_SPI_Slave_flag_RxCpltCallback=TRUE;
	}

}
void udpServer_init(void) {
	// UDP Control Block structure
   struct udp_pcb* upcb = udp_new();
   err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT);  // 7 is the server UDP port

   /* 3. Set a receive callback for the upcb */
   if (err == ERR_OK) {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else {
	   udp_remove(upcb);
   }
}






