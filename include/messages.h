#ifndef MESSAGES
#define MESSAGES

#include <stdint.h>
#include <stdbool.h>

#define CLIENT_MSG_SIZE 63
#define SERV_MSG_SIZE 63
#define FILE_OBJ_SIZE 254
/* Client message */
enum{
    // GET, // get data objects
    RD_INC, // increement reader count
    RD_DEC, // decreement reader count
    READ, //
    ACQ_WL, // acquire write lock
    REL_WL, // release write lock
    WRITE, //
    DEL , // delete file
    RUN , // Run file
    PATCH, // Patch file
    LIST, // list files in server
    BYE, // exit the server
};
typedef struct msg_c{
    uint8_t cmd;
    char data[63];
}msg_c;

void send_to_serv(uint32_t connfd, uint8_t cmd, char* msg);
uint8_t recv_fr_serv(uint32_t connfd);

/* Server msg */

enum{
    CMD_SUCCESS,// cmd succesful at server
    CMD_FAILED, // cmd failed at server
};
typedef struct msg_s{
    uint8_t status;
    char data[63];
}msg_s;

void send_to_client(uint32_t connfd, uint8_t status, char* msg);
msg_c recv_fr_client(uint32_t connfd);


/* both server and client */
typedef struct fileobj{
    uint8_t is_end;
    uint8_t end;
    char data[FILE_OBJ_SIZE]; 
}fileobj;

void send_file(uint32_t fd, uint32_t connfd);
void recv_file(uint32_t fd, uint32_t connfd);
#endif