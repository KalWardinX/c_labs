#include<client.h>

static void read_file(char* path){
    int fd = open(path, O_RDONLY);
    char buffer[BUFFER_SIZE];
    int rd;
    while((rd = read(fd,buffer, BUFFER_SIZE))){
        write(1, buffer, rd);
    }
    write(1, "\n", sizeof("\n"));
}

void c_list_files(int connfd){
    send_to_serv(connfd, LIST, "");    
    char path[PATH_SIZE];
    char* dirlist = strdup("directory_list");
    sprintf(path, "%s/%s", TEMP_DIR, dirlist);
    int fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    recv_file(fd, connfd);
    close(fd);
    read_file(path);
}

void c_read_file(int connfd, char* filename){
    send_to_serv(connfd, RD_INC, filename);
    printf("filename %s", filename);
    fflush(stdout);
    if(recv_fr_serv(connfd) == CMD_FAILED){
        return;
    }
    send_to_serv(connfd, READ, filename);
    char path[PATH_SIZE];
    sprintf(path, "%s/%s",READ_DIR ,filename);
    int fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    recv_file(fd, connfd);
    close(fd);
    
    // run nano
    char nano_cmd[CMD_SIZE];
    sprintf(nano_cmd, "nano -v %s", path);
    system(nano_cmd);
    

    send_to_serv(connfd, RD_DEC, filename);
}

void c_write_file(int connfd, char* filename){
    // acquire write lock
    send_to_serv(connfd, ACQ_WL, filename);
    if(recv_fr_serv(connfd)==CMD_FAILED){
        return;
    }
    send_to_serv(connfd, WRITE, filename);
    // get file to write dir
    char path[PATH_SIZE];
    sprintf(path, "%s/%s",WRITE_DIR ,filename);
    int fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    recv_file(fd, connfd);
    close(fd);
    // copy to read dir
    char cp_cmd[2*CMD_SIZE];
    sprintf(cp_cmd, "cp %s/%s %s/%s", WRITE_DIR, filename, READ_DIR, filename);
    system(cp_cmd);
    // run nano
    char nano_cmd[CMD_SIZE];
    sprintf(nano_cmd, "nano %s", path);
    system(nano_cmd);
    // create patch file
    char patchfile[PATH_SIZE];
    sprintf(patchfile, "%s.patch", filename);
    char diff_cmd[2*CMD_SIZE];
    sprintf(diff_cmd, "diff %s/%s %s/%s > %s/%s", READ_DIR, filename, WRITE_DIR, filename, PATCH_DIR,patchfile);
    system(diff_cmd);

    // patch 
    send_to_serv(connfd, PATCH, filename);
    char patch_path[PATH_SIZE];
    sprintf(patch_path, "%s/%s",PATCH_DIR, patchfile);
    fd = open(patch_path, O_RDONLY);
    send_file(fd, connfd);
    close(fd);

    char out_patch[128];
    sprintf(out_patch, "%s/%s.output", TEMP_DIR, patchfile);
    fd = open(out_patch, O_RDWR|O_CREAT|O_TRUNC, 0644);
    recv_file(fd, connfd);
    close(fd);
    read_file(out_patch);
    send_to_client(connfd, REL_WL, filename);
    // recv_fr_client(connfd);
}

void c_del_file(int connfd, char* filename){
    send_to_serv(connfd, DEL, filename);
    if(recv_fr_serv(connfd)==CMD_SUCCESS){
        printf("File %s successfully deleted.\n", filename);
    }
    else{
        printf("File %s can't be deleted.\n", filename);
    }
}

void c_run_file(int connfd, char* filename){
    send_to_serv(connfd, RD_INC, filename);

    if(recv_fr_serv(connfd)==CMD_FAILED){
        return;
    }
    send_to_serv(connfd, RUN, filename);
    
    char path[PATH_SIZE];
    char output[128];
    sprintf(output, "%s.output",filename);
    sprintf(path,"%s/%s",TEMP_DIR, output);
    int fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    recv_file(fd, connfd);
    close(fd);
    send_to_serv(connfd, RD_DEC, filename);
    read_file(path);
}

void c_help(){
    fprintf(stdout, "TODO :)\n");
    fprintf(stdout, "Commands:\n");
    fprintf(stdout, "\tlist : list files in server\n");
    fprintf(stdout, "\tread <filename>\t\t: read file from server\n");
    fprintf(stdout, "\twrite <filename>\t\t: write file to server\n");
    fprintf(stdout, "\trun <filename>\t\t: run file in server\n");
    fprintf(stdout, "\tdel <filename>\t\t: del file from server\n");
    fprintf(stdout, "\texit          \t\t: exit from server\n");
    fprintf(stdout, "\thelp          \t\t: print this help\n");
    fflush(stdout);
}

void c_exit(int connfd){
    send_to_serv(connfd, BYE, "");
    return ;
}