#include "RTG.h"
#include "my_message.h"

flag_message_From_client=FALSE;

My_message cient_message;

typedef struct resv

{
        uint8_t id;   //
        uint8_t size; //
        char *msg;    //

} resv_t;

resv_t resv;             // Holds
resv_t * p_resv;

void udp_receive_callback(
		void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	flag_message_From_client=1;
	/* Get the IP of the Client */
	const char* remoteIP = ipaddr_ntoa(addr);
	char buf[100];



    resv.id = *(uint8_t *)(p->payload + 0);
    resv.size = *(uint8_t *)(p->payload + 1);
    resv.msg = *(uint8_t *)(p->payload + 2);


	const int len = sprintf (buf,"Hello %s From UDP SERVER\n", (char*)p->payload);

	/* allocate pbuf from RAM*/
	struct pbuf *txBuf = pbuf_alloc(PBUF_TRANSPORT,len, PBUF_RAM);

	/* copy the data into the buffer  */
	pbuf_take(txBuf, buf, len);

	/* Connect to the remote client */
	udp_connect(upcb, addr, port);

	/* Send a Reply to the Client */
	udp_send(upcb, txBuf);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p_tx buffer */
	pbuf_free(txBuf);

	/* Free the p buffer */
	pbuf_free(p);
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

void handle_reception_network()
{
	ethernetif_input(&gnetif);		//Handles the actual reception of bytes from the network interface
	sys_check_timeouts();			//Handle which checks timeout expiration

	if(flag_message_From_client==TRUE)
	{
		printf("res : %c",resv.msg);
		flag_message_From_client==FALSE;
	}
}
