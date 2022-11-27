
#include "stm32f7xx_hal.h"
#include "RTG.h"

//Data for TRANSMINT

uint8_t receivere_UART5_flag_RxCpltCallback=FALSE;
uint8_t receivere_UART4_flag_RxCpltCallback=FALSE;


uint8_t flag_R_Master=FALSE;
uint8_t	flag_R_slave=FALSE;

uint8_t flag_ADC_ConvCpltCallback=FALSE;

uint8_t time_flag_PeriodElapsedCallback=FALSE;



ip_addr_t *addr_global;
u32_t addr_int;
u16_t port_global;
struct pbuf *p_global;
const char* remoteIP_global;
struct pbuf *txBuf;
struct udp_pcb *upcb_global;

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


void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	flag_R_slave=TRUE;
}

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
	time_flag_PeriodElapsedCallback=TRUE;

}

void udp_receive_callback(
		void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	flag_message_From_client=TRUE;
	/* Get the IP of the Client */
	/* Get the IP of the Client */
	addr_global=addr;
    remoteIP_global = ipaddr_ntoa(addr);

	upcb_global=upcb;

	port_global=port;
	p_global=p;

	const int len =handleMessageFromClient(p);
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



