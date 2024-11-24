#ifndef CONNECTIONQUEUE
#define CONNECTIONQUEUE
/* Connection Queue */
typedef struct connection{
    int connfd;
    struct connection* next;
}connection;

typedef struct {
    connection* front;
    connection* rear;
    pthread_mutex_t q_lock;
}conn_queue;


conn_queue* conn_queue_init();

void enqueue(conn_queue* t, int connfd);

connection* dequeue(conn_queue* t);

#endif