#ifndef MY_MESSAGE_H_
#define MY_MESSAGE_H_

enum MessageType{
	INFO,
	GET,
	POST,
	UPDATE,
	SEND
};


typedef struct my_message

{
        uint8_t id;
        uint8_t Peripheral;
        uint8_t Iterations;
        uint8_t length ;
        uint8_t  msg[50];

} my_message;

void my_message_toString();


#endif /* INC_RTG_H_ */
