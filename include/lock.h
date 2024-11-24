/* READERS-WRITER LOCK */
#ifndef RWLOCK
#define RWLOCK

#include <pthread.h>

typedef struct rwlock{
    pthread_mutex_t r;
    pthread_mutex_t w;
    int r_count;
}rwlock;

rwlock* init_lock();
void del_lock(rwlock* );

int begin_read(rwlock* );
int end_read(rwlock* );

int begin_write(rwlock* );
int end_write(rwlock*);
#endif