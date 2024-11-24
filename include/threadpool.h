#ifndef THREADPOOL
#define THREADPOOL

typedef struct threadpool{
    pthread_t *thread;
    pthread_cond_t cv;
    pthread_mutex_t cv_lock;
    int thread_cnt;
}threadpool;

threadpool* threadpool_init(int);

int threadpool_assign_func(threadpool* , void* func, void* arg);

void thread_awake(threadpool* tp);

void threadpool_join(threadpool*);

void thread_wait(threadpool*);
#endif