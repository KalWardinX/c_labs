#include <c_labs.h>


conn_queue* conn_queue_init(){
    conn_queue* temp = (conn_queue*)malloc(sizeof(conn_queue));
    temp->front = NULL;
    temp->rear = NULL;
    pthread_mutex_init(&(temp->q_lock),NULL);
    return temp;
}
void enqueue(conn_queue* t, int connfd){
    pthread_mutex_lock(&(t->q_lock));
    connection* temp = (connection*) malloc(sizeof(connection));
    temp->connfd = connfd;
    temp->next = NULL;
    if(t->front == NULL){
        t->front = temp;
        t->rear = temp;
    }
    else{
        t->rear->next = temp;
        t->rear = temp;
    }
    pthread_mutex_unlock(&(t->q_lock));
    return;
}
connection* dequeue(conn_queue* t){
    pthread_mutex_lock(&(t->q_lock));
    connection* temp=NULL;
    if(t->front == t->rear){
        temp = t->front;
        t->front = NULL;
        t->rear = NULL;
    }
    else{
        temp = t->front;
        t->front = t->front->next;
    }
    pthread_mutex_unlock(&(t->q_lock));
    return temp;
}