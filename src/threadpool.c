#include <c_labs.h>

threadpool* threadpool_init(int thread_cnt){
    threadpool *temp = malloc(sizeof(threadpool));
    pthread_cond_init(&(temp->cv), NULL);
    pthread_mutex_init(&(temp->cv_lock), NULL);
    temp->thread_cnt = thread_cnt;
    temp->thread = malloc(sizeof(pthread_t ) * thread_cnt);
    return temp;
}

int threadpool_assign_func(threadpool* tp, void* func, void* arg){
    for( int i=0; i<tp->thread_cnt; i++){
        if(pthread_create(tp->thread+i, NULL, func, arg)){
            return -1;
        }
    }
    return 0;
}

void thread_awake(threadpool* tp){
    pthread_cond_broadcast(&(tp->cv));
}

void threadpool_join(threadpool* tp){
    for(int i=0; i<tp->thread_cnt; i++){
        pthread_join(tp->thread[i], NULL);
        fprintf(stdout,"Thread %d reaped.\n",i);
    }    
}

void thread_wait(threadpool* tp){
    pthread_mutex_lock(&tp->cv_lock);
    pthread_cond_wait(&tp->cv, &tp->cv_lock);
    pthread_mutex_unlock(&tp->cv_lock);
}