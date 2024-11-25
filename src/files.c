#include<c_labs.h>
file* getfile(char* filename){
    // printf("getfile here\n");
    file* temp = malloc(sizeof(file));
    temp->filename = strdup(filename);
    temp->lock = init_lock();
    // pthread_mutex_init(&temp->r, NULL);
    // pthread_mutex_init(&temp->w, NULL);
    // temp->r_count = 0;

    return temp;
}

bool delfile(file* f){
    del_lock(f->lock);
    // pthread_mutex_destroy(&f->r);
    // pthread_mutex_destroy(&f->w);
    free(f->filename);
    return true;
}

files* init_files(int capacity){
    files* f = malloc(sizeof(files));
    f->end = 0;
    f->capacity = capacity;
    f->filearr = malloc(sizeof(file)*capacity);
    return f;
}

int file_exists(files* f, char* filename){
    for( int i=0; i<f->end; i++){
        if  (strcmp(f->filearr[i]->filename, filename)==0)
            return i;
    }
    return -1;
}

int search_file(files* f, char* filename){
    // printf("file %s \n", filename);
    for( int i=0; i<f->end; i++){
        if  (strcmp(f->filearr[i]->filename, filename)==0){
            // printf("index %d\n",i);
            return i;
        }
            
    }
}
int submit_file(files* f, char* filename){
    if(f->end == f->capacity){
        return 0;
    }
    file* temp = malloc(sizeof(file));
    // printf()
    temp = getfile(filename);
    f->filearr[f->end] = temp;
    f->end++;
    return 1;
}

int unsubmit_file(files* f, char* filename){
    int ind = -1;
    if((ind = file_exists(f, filename))==-1){
        // printf("something went wrong\n");
        return 0;
    }
    delfile(f->filearr[ind]);
    for(int i=ind+1; i<f->end; i++){
        f->filearr[i-1] = f->filearr[i];
    }
    f->end--;
    return 1;
}

int first_init(files* f){
    DIR *dp;
    struct dirent *i;     
    dp = opendir (FILE_DIR);
    // printf("start here\n");
    fflush(stdout);
    if (dp != NULL)
    {
        while ((i = readdir (dp)) != NULL){
            if(strcmp(i->d_name, ".")==0 || strcmp(i->d_name,"..")==0){
                continue;
            }
            submit_file(f, i->d_name);
        }
        closedir (dp);

        return 0;
    }
    else
    {
        perror ("Couldn't open the directory");
        return -1;
    }
}

bool acquire_writelock(files* f, char* filename){
    int index = search_file(f, filename);
        // printf("index %d\n", index);
    // pthread_mutex_lock(&f->filearr[index]->w);
    begin_write(f->filearr[index]->lock);
        // printf("lock acq wrt\n");

}
bool release_writelock(files* f, char* filename){
    int index = search_file(f, filename);
    // pthread_mutex_unlock(&f->filearr[index]->w);
    end_write(f->filearr[index]->lock);
}

bool acquire_readlock(files*f , char* filename){
    int index = search_file(f, filename);
    begin_read(f->filearr[index]->lock);
//     pthread_mutex_lock(&f->filearr[index]->r);
//     f->filearr[index]->r_count++;
//     if(f->filearr[index]->r_count==1)
//         pthread_mutex_lock(&f->filearr[index]->w);
//     pthread_mutex_unlock(&f->filearr[index]->r);
}
bool release_readlock(files*f , char* filename){
    int index = search_file(f, filename);
    end_read(f->filearr[index]->lock);

    // pthread_mutex_lock(&f->filearr[index]->r);
    // f->filearr[index]->r_count--;
    // if(f->filearr[index]->r_count==0)
    //     pthread_mutex_unlock(&f->filearr[index]->w);
    // pthread_mutex_unlock(&f->filearr[index]->r);
}