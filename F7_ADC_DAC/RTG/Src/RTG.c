#include "RTG.h"

/*
 *	This example will show how to transmit and receive
 *	packets using the LWIP. The following code will
 *	program the EVB to be an echo server.
 *
 *	EVB configuration:
 *	IP: 		192.168.1.1
 *	NETMASK: 	255.255.255.0 (or 0.0.0.0/24)
 *	GATEWAY: 	192.168.1.100 (not in use but required by IDE)
 *	Port:		7 (recommended 50,000+)
 */

void rtg_main()    {
	printf("Start of program\n\r");
	udpServer_init();					//UDP server initialization
	while (1) {
		handle_reception_network();

	}
}
