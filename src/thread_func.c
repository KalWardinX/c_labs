#include <c_labs.h>
#include <dirent.h>
#define BUFFER_SIZE 512
extern files* files_list;
static void read_file(char* path){
    int fd = open(path, O_RDONLY);
    char buffer[BUFFER_SIZE];
    int rd;
    while((rd = read(fd,buffer, BUFFER_SIZE))){
        write(1, buffer, rd);
    }
    write(1, "\n", sizeof("\n"));
}
/* PYTHON function defined in src/python.c */
void* thread_func(void* arg){
    args* a = (args*)arg;
    conn_queue* cq = a->cq;
    threadpool* tp = a->tp;
    while(1){
        connection* temp = dequeue(cq);
        if(temp!=NULL){
            // PyThreadState* thread_state;
            // PyInterpreterConfig config;
            // memset(&config, 0, sizeof(config));
            // config.gil = PyInterpreterConfig_OWN_GIL;
            // config.allow_threads = 1;
            // config.check_multi_interp_extensions = 1;
            // Py_NewInterpreterFromConfig(&thread_state, &config);
            // // redirect output of python stdout to a file
            // PyRun_SimpleString("import sys");
            
            // if(thread_state!=NULL){
                while(1){
                    msg_c m = recv_fr_client(temp->connfd);
                    if(parse(m, temp->connfd)){
                        break;
                    }
                }
            // }
            close(temp->connfd);
            // Py_EndInterpreter(thread_state);
            free(temp);
        }
        else{
            thread_wait(tp);
        }
    }
}

int parse(msg_c m, int connfd){
    switch(m.cmd){
        case RD_INC:
            inc_readers(connfd, m.data);
            break;
        case RD_DEC:
            dec_readers(connfd,m.data);
            break;
        case READ:
            s_read(connfd, m.data);
            break;
        case ACQ_WL:
            acq_wl(connfd, m.data);
            break;
        case REL_WL:
            rel_wl(connfd, m.data);
            break;
        case WRITE:
            s_write(connfd, m.data);
            break;
        case DEL:
            del(connfd, m.data);
            break;
        case RUN:
            run(connfd, m.data);
            break;
        case PATCH:
            patch(connfd, m.data);
            break;
        case LIST:
            list(connfd);
            break;
        case BYE:
            return 1;
            break;
        default:
            write(1, "SOMETHING WENT WRONG\n", 22);
            return 1;
    }
    return 0;
}
/*
void imp{
    char redirect[100];
    char opfile[30];
    sprintf(opfile, "op_%lu.txt", pthread_self());
    sprintf(redirect, "f = open('%s','w')", opfile);
    PyRun_SimpleString(redirect);
    PyRun_SimpleString("__stdout = sys.stdout\nsys.stdout = f");
    PyRun_SimpleString("__stderr = sys.stderr\nsys.stderr = f");

    PyRun_SimpleString(pythonString);
    PyRun_SimpleString("f.close()\nsys.stdout=__stdout\nsys.stderr=__stderr");
    char output[2048]={'\0'};
    strcpy(output, "Y: ");
    int fd = open(opfile, O_RDONLY);
    int rd = read(fd, output+3, 2045);
    output[rd+3] = '\0';
    if(rd==0){
        send(temp->connfd, "N: ", 4,0);
    }else{
        send(temp->connfd, output, rd+3, 0);
    }

}
*/
static void listdir(int fd, char* path){
    DIR *dp;
    struct dirent *f;     
    dp = opendir (path);
    printf("start here\n");
    fflush(stdout);
    if (dp != NULL)
    {
        while ((f = readdir (dp)) != NULL){
            write(fd, f->d_name, strlen(f->d_name));
            write(fd, "\n", 1);
        }
        closedir (dp);
        printf("here\n");
        fflush(stdout);
        return;
    }
    else
    {
        perror ("Couldn't open the directory");
        return ;
    }
}

static bool check_file(char* path, char* file){
    DIR *dp;
    struct dirent *f;     
    dp = opendir (path);
    printf("start here\n");
    fflush(stdout);
    if (dp != NULL)
    {
        while ((f = readdir (dp)) != NULL){
            if (strcmp(f->d_name, file) == 0){
                return true;
            }
        }
        closedir (dp);

        return false;
    }
    else
    {
        perror ("Couldn't open the directory");
        return false;
    }
}

void inc_readers(int connfd, char* filename){
    if(!check_file(FILE_DIR, filename)){
        send_to_client(connfd, CMD_FAILED, "File doesn't exist in sever");
        return;
    }
    acquire_readlock(files_list, filename);
    // increement readers
    send_to_client(connfd, CMD_SUCCESS, "File ready to read");
    
}
void dec_readers(int connfd, char* filename){
    release_readlock(files_list, filename);
}
void acq_wl(int connfd, char* filename){
    char file_path[PATH_SIZE];
    sprintf(file_path, "%s/%s", FILE_DIR, filename);
    if(!check_file(FILE_DIR, filename)){
        submit_file(files_list, filename);
        int fd = open(file_path, O_RDWR|O_TRUNC|O_CREAT, 0644);
        close(fd);
    }
        printf("acquiring wrt\n");

        fflush(stdout);

    acquire_writelock(files_list, filename);
        printf("lock acq wrt\n");
        fflush(stdout);

    send_to_client(connfd, CMD_SUCCESS, "Sending File");
}
void rel_wl(int connfd, char* filename){
    release_writelock(files_list, filename);
}

void s_read(int connfd, char* filename){
    char path[PATH_SIZE];
    sprintf(path, "%s/%s",FILE_DIR ,filename);
    printf("path %s", path);
    fflush(stdout);
    // read_file(path);

    int fd = open(path, O_RDONLY);
    
    send_file(fd, connfd);
    close(fd);
}
void s_write(int connfd, char* filename){
    printf("hello write\n");
    fflush(stdout);
    char path[PATH_SIZE];
    sprintf(path, "%s/%s",FILE_DIR ,filename);
    printf("path %s", path);
    fflush(stdout);
    // send_file(path);

    int fd = open(path, O_RDONLY);
    
    send_file(fd, connfd);
    close(fd);
}

void run(int connfd, char* filename){
    // send_to_client(connfd, CMD_SUCCESS, "success");
    char path[PATH_SIZE];
    sprintf(path, "%s/%s",FILE_DIR ,filename);
    printf("path %s", path);
    fflush(stdout);
    char cmd[128];
    char output[128];
    sprintf(output,"%s/%s.output", TEMP_DIR, filename);
    sprintf(cmd, "python %s &> %s",path, output);
    system(cmd);
    int fd = open(output, O_RDONLY);
    send_file(fd, connfd);
    close(fd);
}
void patch(int connfd, char* filename){
    char path[PATH_SIZE];
    sprintf(path, "%s/%s.patch",PATCH_DIR ,filename);
    printf("path %s", path);
    int fd = open(path, O_RDWR|O_CREAT|O_TRUNC, 0644);
    recv_file(fd, connfd);
    close(fd);
    char patch_cmd[128];
    sprintf(patch_cmd, "patch %s/%s %s &> %s/%s.patch.output", FILE_DIR, filename, path, TEMP_DIR, filename);
    system(patch_cmd);

    char out_patch[128];
    sprintf(out_patch, "%s/%s.patch.output", TEMP_DIR, filename);
    fd = open(out_patch, O_RDONLY);
    send_file(fd, connfd);
    close(fd);
}

void del(int connfd, char* filename){
    if(!check_file(FILE_DIR, filename)){
        send_to_client(connfd, CMD_FAILED, "file doesn't exist.");
        return;
    }
    
    // acquire lock
    acquire_writelock(files_list, filename);
    if (0/* acquire lock*/){
        send_to_client(connfd, CMD_FAILED, "file is busy. try again later.");
        return ;
    }
    char path[PATH_SIZE];
    sprintf(path, "%s/%s", FILE_DIR, filename);
    if (remove(path)==0){
        send_to_client(connfd, CMD_FAILED, "File deleted successfully");
        // release lock
        release_writelock(files_list, filename);
        // unsubmit file
        unsubmit_file(files_list, filename);
    }
    else{
        send_to_client(connfd, CMD_FAILED, "can't delete file");
    }

}

void list(int connfd){
    printf("in list\n");
    fflush(stdout);
    char path[PATH_SIZE];
    sprintf(path, "%s/list_%lu,txt", TEMP_DIR, pthread_self());
    printf("path %s\n", path);
    int fd = open(path, O_CREAT|O_RDWR|O_TRUNC, 0644);
    listdir(fd, FILE_DIR);
    close(fd);

    fd = open(path , O_RDONLY);
    send_file(fd, connfd);
    close(fd);
    printf("done\n");
}