#ifndef SERVER_ETH_TOOLS_
#define SERVER_ETH_TOOLS_

void send_to_cient(my_message receive_client_message );
int handleMessageFromClient(struct pbuf *p);
result_test  run_client_test(my_message receive_client_message);
void handle_reception_network();

#endif /* SERVER_ETH_TOOLS_ */
