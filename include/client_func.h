#ifndef CLIENT_FUNC
#define CLIENT_FUNC

#define PATH_SIZE 64
void c_list_files(int connfd);
void c_read_file(int connfd, char* filename);
void c_write_file(int connfd, char* filename);
void c_run_file(int connfd, char* filename);
void c_del_file(int connfd, char* filename);
void c_exit(int connfd);
void c_help();

#endif