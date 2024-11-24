#ifndef THREAD_FUNC
#define THREAD_FUNC
#include<messages.h>

/* args */

typedef struct args{
    conn_queue *cq;
    threadpool *tp;
}args;

/* PYTHON function definded in src/python.c */
void* thread_func(void* arg);
int parse(msg_c m, int connfd);

void inc_readers(int connfd, char* filename);
void dec_readers(int connfd, char* filename);

void acq_wl(int connfd, char* filename);
void rel_wl(int connfd, char* filename);

void s_read(int connfd, char* filename);
void s_write(int connfd, char* filename);
void run(int connfd, char* filename);
void patch(int connfd, char* filename);

void del(int connfd, char* filename);
void list(int connfd);

#endif