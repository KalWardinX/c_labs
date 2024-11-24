#ifndef FILES
#define FILES
#include <lock.h>
#include <stdbool.h>
typedef struct file{
    rwlock* lock;
    char* filename;
}file;

// typedef struct file{
//     pthread_mutex_t r;
//     pthread_mutex_t w;
//     int r_count;
//     char* filename;
// }file;
file* getfile(char* filename);
bool delfile(file* f);

typedef struct files{
    file** filearr;
    int end;
    int capacity;
} files;


files* init_files(int capacity);
int file_exists(files* f, char* filename);
int submit_file(files* f, char* filename);
int unsubmit_file(files* f, char* filename);

int first_init(files* f);

bool acquire_writelock(files* f, char* filename);
bool release_writelock(files* f, char* fillename);

bool acquire_readlock(files*f , char* filename);
bool release_readlock(files*f , char* filename);

#endif