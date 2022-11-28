#include "RTG.h"
#include "my_message.h"

flag_message_From_client=FALSE;

result_test result;

my_message receive_client_message;

//send the result to client
void send_to_cient(my_message receive_client_message )
{


	/* copy the data into the buffer  */
	char buf[100];
	uint8_t id;
	printf("\r\n send data... \r\n");
	buf[my_message_id_index]=receive_client_message.id;
	buf[my_message_Peripheral_index]=receive_client_message.Peripheral;
	buf[my_message_Iterations_index]=receive_client_message.Iterations;
	buf[my_message_length_index]=receive_client_message.length;
	for (int i= 0,j=my_message_msg_index; i <= receive_client_message.length; i++)
	{
		buf[j++]=receive_client_message.msg[i];
	}

	addr_global->addr=ADDR_;


	/* allocate pbuf from RAM*/
	txBuf = pbuf_alloc(PBUF_TRANSPORT,14, PBUF_RAM);
	/* copy the data into the buffer  */
	pbuf_take(txBuf, buf, 14);
	/* Connect to the remote client */
	udp_connect(upcb_global, addr_global, port_global);

	/* Send a Reply to the Client */
	udp_send(upcb_global, txBuf);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb_global);

	/* Free the p_tx buffer */
	pbuf_free(txBuf);

	/* Free the p buffer */
	pbuf_free(p_global);
}

// handle Message From Client
int handleMessageFromClient(struct pbuf *p)
{
	receive_client_message.id= *(uint8_t *)(p->payload + my_message_id_index);
	receive_client_message.Peripheral= *(uint8_t *)(p->payload + my_message_Peripheral_index);
	receive_client_message.Iterations= *(uint8_t *)(p->payload + my_message_Iterations_index);
	receive_client_message.length= *(uint8_t *)(p->payload + my_message_length_index);
	// save into buffer
	memcpy(receive_client_message.msg , (p->payload + my_message_msg_index),  receive_client_message.length);

	return my_message_msg_index+receive_client_message.length;
}

//run the correct test
result_test  run_client_test(my_message receive_client_message)
{
	result_test result={FALSE,"ERROR"};
	uint8_t iteration=receive_client_message.Iterations;
	switch(receive_client_message.Peripheral)
  	{
	int result1 ;
  		case TEST_UART:
  			for (uint8_t i = 0; i < iteration ; i++)
  			{
  				UART_tests(receive_client_message.msg,receive_client_message.length,receive_client_message.Iterations,&result);
  				if(result.bool_test ==FALSE )
  					return result;
  			}
  			print_result_test(result);
  			return result;


  		case TEST_I2C:

  			for (uint8_t i = 0; i < iteration ; i++)
  			{
  				I2C_tests(receive_client_message.msg,receive_client_message.length,receive_client_message.Iterations,&result);
  			  	if(result.bool_test ==FALSE )
  			  		return result;
  			}
  			print_result_test(result);
  			return result;

  		case TEST_SPI:

  		  	for (uint8_t i = 0; i < iteration ; i++)
  		  	{
  		  		SPI_tests(receive_client_message.msg,receive_client_message.length,receive_client_message.Iterations,&result);
  		  		if(result.bool_test ==FALSE )
  		  		return result;
  		  	}
  		  	print_result_test(result);
  		  	return result;

  		case TEST_ADC:
  			for (uint8_t i = 0; i < iteration ; i++)
  			{
  				ADC_tests(&result);
  			  	if(result.bool_test ==FALSE )
  			  		return result;
  			}
  			 print_result_test(result);
  			 return result;

  		case Test_TIMER:

  		  	for (uint8_t i = 0; i < iteration ; i++)
  		  	{
  		  		timer_test(&result);
  		  		if(result.bool_test ==FALSE )
  		  			return result;
  		  	}
  		  			 print_result_test(result);
  		  			 return result;
  		default:

  			break;
  	}

	return result;
}

//handle reception network
void handle_reception_network()
{
	//Handles the actual reception of bytes from the network interface
	ethernetif_input(&gnetif);
	//Handle which checks timeout expiration
	sys_check_timeouts();

	//got reception network
	if(flag_message_From_client==TRUE)
	{
		result=run_client_test(receive_client_message);

		receive_client_message.length=strlen(result.msg);
		memcpy(receive_client_message.msg , result.msg,  receive_client_message.length );
		//send client message
		send_to_cient(receive_client_message  ) ;

		flag_message_From_client=FALSE;
	}
}






