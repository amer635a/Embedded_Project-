#ifndef SERVER_ETH_TOOLS_
#define SERVER_ETH_TOOLS_

//send the result for client
void send_to_cient(my_message receive_client_message );

//handle message from client and test
int handleMessageFromClient(struct pbuf *p);

//run the client test
result_test  run_client_test(my_message receive_client_message);

//handle reception network
void handle_reception_network();

#endif /* SERVER_ETH_TOOLS_ */
