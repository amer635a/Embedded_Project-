
#ifndef INC_RTG_H1_
#define INC_RTG_H1_

#include "main.h"
#include "lwip.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Boolean    */
#define TRUE 1
#define FALSE 0

/*  UART    */
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;		//Change to match your UART number
extern UART_HandleTypeDef huart5;		//Change to match your UART number

#define UART_4 &huart4				    //Change to match your UART number
#define UART_5 &huart5				    //Change to match your UART number
#define UART_DEBUG &huart3

/*  SPI    */
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

#define SPI_1 &hspi1
#define SPI_4 &hspi4

#define SPI_MASTER SPI_1
#define SPI_SLAVE  SPI_4

/*  DAC    */
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
#define DAC_1 &hdac
#define ADC_1 &hadc1


/*  Timer    */
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim1;
#define TIM_2 &htim2
#define TIM_1 &htim1

/*  I2C    */
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
#define I2C_1 &hi2c1
#define I2C_2 &hi2c2
#define I2C_MASTER I2C_1
#define I2C_SLAVE I2C_2
#define SLAVE_ADRESS_I2C1 44


/*  Peripheral    */
#define Test_TIMER 1
#define TEST_UART  2
#define TEST_SPI   4
#define TEST_I2C   8
#define TEST_ADC   16


/*  Callback variable    */
extern int adc_flag ; //flag for ADC Interrupt
extern uint8_t receivere_UART5_flag_RxCpltCallback;
extern uint8_t receivere_UART4_flag_RxCpltCallback;
extern uint8_t receive_SPI_Master_flag_RxCpltCallback;
extern uint8_t receive_SPI_Slave_flag_RxCpltCallback;
extern uint8_t flag_R_Master;
extern uint8_t	flag_R_slave;
extern uint8_t flag_ADC_ConvCpltCallback;
extern uint8_t time_flag_PeriodElapsedCallback;
extern uint32_t PeriodElapsedCallback_couter_timer1 ;
extern uint32_t PeriodElapsedCallback_couter_timer2 ;

#define SIZEOF_DATA_BUFF  18
extern uint8_t data_buff_transmint[SIZEOF_DATA_BUFF];
extern uint8_t data_buff_receivere[SIZEOF_DATA_BUFF];

extern uint32_t address_global;

/*  LED   */
#define GPIO_PER_1 GPIOB
#define GPIO_PER_2 GPIOB
#define GPIO_PER_3 GPIOB
#define GPIO_PER_4 GPIOC
#define GPIO_LED_1 LD1_Pin
#define GPIO_LED_2 LD2_Pin
#define GPIO_LED_3 LD3_Pin



/*  LWIP    */

#define SERVER_PORT 7
extern struct netif gnetif;	//Generic data structure used for all lwIP network interfaces.
#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13


#define MAX_WAITING_COUNTER 5



// udp variable
extern flag_message_From_client;
extern ip_addr_t  addr_global;
extern u32_t addr_int;
extern u16_t port_global;
extern struct pbuf *p_global;
extern const char* remoteIP_global;
extern struct pbuf *txBuf;
extern struct udp_pcb *upcb_global;
#define ADDR_ 16885952
extern u32_t addr_TRY_GOLABL;
#define SIZE_OF_BUFFER 100
#define SIZE_FIRST_ELEMENT_MY_MESSAGE 4


typedef struct result_test
{
	uint8_t bool_test;
	uint8_t  msg[SIZE_OF_BUFFER];
} result_test;

void rtg_main();

#endif

