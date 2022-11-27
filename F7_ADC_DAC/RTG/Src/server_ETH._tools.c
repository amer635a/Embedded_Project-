#include "RTG.h"
#include "my_message.h"

flag_message_From_client=FALSE;
//flag_message_From_client=TRUE;
ip_addr_t *addr_global;
my_message receive_client_message;
struct pbuf *txBuf;
struct udp_pcb *upcb_global;

u32_t addr_int;
u16_t port_global;
struct pbuf *p_global;
const char* remoteIP_global;

void save_client_data(int len)
{





}

void send_to_cient(my_message receive_client_message )
{


	/* copy the data into the buffer  */
	char buf[100];
	uint8_t id;
	printf("\r\n send data... \r\n");
	buf[0]=receive_client_message.id;
	buf[1]=receive_client_message.Peripheral;
	buf[1]=receive_client_message.Iterations;
	buf[2]=receive_client_message.length;
	buf[3]='A';
	buf[4]='M';
	buf[5]=0;
	addr_global->addr=16885952;
	printf("\r\n addr_global:->%d \r\n",addr_global->addr);
	printf("\r\n port_global:->%d \r\n",port_global);

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

int initialization_receive_client_message(struct pbuf *p)
{
	receive_client_message.id= *(uint8_t *)(p->payload + 0);
	receive_client_message.Peripheral= *(uint8_t *)(p->payload + 1);
	receive_client_message.Iterations= *(uint8_t *)(p->payload + 2);
	receive_client_message.length= *(uint8_t *)(p->payload + 3);

	memcpy(receive_client_message.msg , (p->payload + 4),  receive_client_message.length);

	return 4+receive_client_message.length;
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

	const int len =initialization_receive_client_message(p);

	save_client_data(len);



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


result_test result;
void handle_reception_network()
{
	ethernetif_input(&gnetif);		//Handles the actual reception of bytes from the network interface
	sys_check_timeouts();			//Handle which checks timeout expiration


	if(flag_message_From_client==TRUE)
	{
		result=run_client_test(receive_client_message);
		send_to_cient(receive_client_message  ) ;

		flag_message_From_client=FALSE;
	}
}





//		receive_client_message.id=1;
//		receive_client_message.Peripheral=2;
//		receive_client_message.Iterations=2;
//		receive_client_message.length=3;
//		receive_client_message.msg[0]='A';
//		receive_client_message.msg[1]='M';
//		receive_client_message.msg[2]=0;


//		receive_client_message.id=1;
//		receive_client_message.Peripheral=8;
//		receive_client_message.Iterations=2;
//		receive_client_message.length=3;
//		receive_client_message.msg[0]='A';
//		receive_client_message.msg[1]='M';
//		receive_client_message.msg[2]=0;

//		receive_client_message.id=1;
//		receive_client_message.Peripheral=16;
//		receive_client_message.Iterations=2;
//		receive_client_message.length=3;
//		receive_client_message.msg[0]='A';
//		receive_client_message.msg[1]='M';
//		receive_client_message.msg[2]=0;

//		receive_client_message.id=1;
//		receive_client_message.Peripheral=1;
//		receive_client_message.Iterations=2;
//		receive_client_message.length=3;
//		receive_client_message.msg[0]='A';
//		receive_client_message.msg[1]='M';
//		receive_client_message.msg[2]=0;
