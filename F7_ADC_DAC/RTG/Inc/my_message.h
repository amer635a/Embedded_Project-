#ifndef MY_MESSAGE_H_
#define MY_MESSAGE_H_


// my_message index features
#define my_message_id_index 0
#define my_message_Peripheral_index 1
#define my_message_Iterations_index 2
#define my_message_length_index 3
#define my_message_msg_index 4



//struct for saving and send data between server and client
typedef struct my_message

{
        uint8_t id;
        uint8_t Peripheral;
        uint8_t Iterations;
        uint8_t length ;
        uint8_t  msg[50];

} my_message;




#endif /* INC_RTG_H_ */
