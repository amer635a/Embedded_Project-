#include "RTG.h"
#include "my_message.h"
#include "server_ETH_tools.h"
/*
   uint8_t id;
   uint8_t Peripheral;
   uint8_t Iterations;
   uint8_t length ;
   uint8_t  msg[SIZE_OF_BUFFER];
   */


void print_test(uint8_t result,uint8_t counter, uint8_t * test_name)//bool answer, int counter, std::string test_name
{
	if(result==TRUE)
		printf("Test succes %d + %s \r\n",counter,test_name);
	else
		printf("Test succes %d + %s \r\n",counter,test_name);
}

uint8_t Peripheral_part_invalid_test()
{
	my_message receive_client_message_simulation;
	result_test actual_result;
	uint8_t test_counter=1;
	uint8_t invalid_input=0;
	uint8_t expected_result=FALSE;

	put_value_on_client_message(&receive_client_message_simulation, 1,invalid_input,2,3,"AM");


	actual_result=run_client_test(receive_client_message_simulation);

	return ( expected_result==actual_result.bool_test);
}


void test_function_handle_message_from_client()
{
	printf("*** start test_function_handle_message_from_client ***\r\n");

	uint8_t test_counter=1;
	uint8_t invalid_input=0;

	print_test (  Peripheral_part_invalid_test(),test_counter,"Peripheral_part_isZero_test");

}



void run_UART_tests()
{

	printf("*** run_UART_tests ***\r\n");
	my_message receive_client_message_simulation;
	uint8_t test_counter=1;
	uint8_t invalid_input=0;

}
void run_ADC_tests()
{

}
void run_I2C_tests()
{

}
void run_SPI_tests()
{

}
void run_Timer_tests()
{

}

void put_value_on_client_message(my_message *client_message,uint8_t test_id,
		 uint8_t test_Peripheral,uint8_t test_Iterations ,uint8_t test_msg_length ,uint8_t *test_msg)
{
	client_message->id=test_id;
	client_message->Peripheral=test_Peripheral;
	client_message->Iterations=test_Iterations;
	client_message->length=test_msg_length;
	memcpy(client_message->msg , test_msg,   test_msg_length);
}


void start_unit_test(){
	printf("*** Start test mode ***\r\n");


	test_function_handle_message_from_client();
	run_UART_tests();
	run_ADC_tests();
	run_I2C_tests();
	run_SPI_tests();
	run_Timer_tests();



}
