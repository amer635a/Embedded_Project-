#ifndef MY_MESSAGE_H_
#define MY_MESSAGE_H_

enum MessageType{
	INFO,
	GET,
	POST,
	UPDATE,
	SEND
};


typedef struct my_message{
	uint8_t msgID;
	uint8_t *clientAddress;
	uint8_t * content;
} My_message;


void my_message_toString();


#endif /* INC_RTG_H_ */
