#include<messages.h>
#include<c_labs.h>

/* client side */
void send_to_serv(uint32_t connfd, uint8_t cmd, char* msg){
    msg_c *m = malloc(sizeof(msg_c));
    m->cmd = cmd;
    strcpy(m->data, msg);
    send(connfd, m, sizeof(msg_c), 0);
    // fprintf(stdout, "SENT: [ cmd: %d || msg: '%s' ]\n", m->cmd ,m->data);
    free(m);
}

uint8_t recv_fr_serv(uint32_t connfd){
    msg_s *recv_msg = malloc(sizeof(msg_s));
    recv(connfd, recv_msg, sizeof(msg_s), 0);
    // fprintf(stdout, "RECV: [ status: %d || msg: '%s' ]\n", recv_msg->status ,recv_msg->data);
    uint8_t status = recv_msg->status;
    free(recv_msg);
    return status;
}


/* server side */
void send_to_client(uint32_t connfd, uint8_t status, char* msg){
    msg_s *m = malloc(sizeof(msg_s));
    m->status = status;
    strcpy(m->data, msg);
    send(connfd, m, sizeof(msg_s), 0);
    // fprintf(stdout, "SENT: [ status: %d || msg: '%s' ]\n", m->status ,m->data);
    free(m);
}

msg_c recv_fr_client(uint32_t connfd){
    msg_c *m = malloc(sizeof(msg_c));
    msg_c temp;
    recv(connfd, m, sizeof(msg_c), 0);
    // fprintf(stdout, "RECV: [ cmd: %d || msg: '%s' ]\n", m->cmd ,m->data);
    temp.cmd = m->cmd;
    strcpy(temp.data, m->data);
    free(m);
    return temp;
}


/* send and recv files */
void send_file(uint32_t fd, uint32_t connfd){
    fileobj f;
    printf("send start\n");
    f.is_end = 0;
    while((f.end = read(fd, f.data, sizeof(FILE_OBJ_SIZE)))){
        // printf("file %u %u %s\n", f.is_end, f.end, f.data);
        send(connfd, &f, sizeof(f), 0);
        memset(f.data, 0, FILE_OBJ_SIZE);
    }
    printf("send end\n");

    f.is_end = 1;
    f.end=0;
    memset(f.data, 0, FILE_OBJ_SIZE);
    send(connfd, &f, sizeof(f), 0);
    return ;
}

void recv_file(uint32_t fd, uint32_t connfd){
    fileobj f;
    printf("start recv\n");
    while(1){
        memset(&f, 0, sizeof(f));
        recv(connfd, &f, sizeof(f), 0);
        if(f.is_end){
            break;
        }
        write(fd, f.data, f.end);
    }
    printf("done\n");
    return ;
}