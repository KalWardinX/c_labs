#include <c_labs.h>

rwlock* init_lock(){
    rwlock* lock = malloc(sizeof(rwlock));
    pthread_mutex_init(&lock->r, NULL);
    pthread_mutex_init(&lock->w, NULL);
    lock->r_count = 0;
    return lock;
}
void del_lock(rwlock* lock){
    pthread_mutex_destroy(&lock->r);
    pthread_mutex_destroy(&lock->w);
    free(lock);
}

int begin_read(rwlock* lock){
    pthread_mutex_lock(&lock->r);
    lock->r_count++;
    // printf("read count begin read %d\n", lock->r_count);
    fflush(stdout);
    if(lock->r_count==1)
        pthread_mutex_lock(&lock->w);
    pthread_mutex_unlock(&lock->r);
}

int end_read(rwlock* lock){
    pthread_mutex_lock(&lock->r);
    lock->r_count--;
    // printf("read count end read %d\n", lock->r_count);
    fflush(stdout);
    if(lock->r_count==0)
        pthread_mutex_unlock(&lock->w);
    pthread_mutex_unlock(&lock->r);
}

int begin_write(rwlock* lock){
    pthread_mutex_lock(&lock->w);
}

int end_write(rwlock* lock){
    pthread_mutex_unlock(&lock->w);
}