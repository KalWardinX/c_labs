#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Python.h> // for python environment
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h> // contains addrinfo and getaddrinfo
#include <errno.h>
#include <conn_queue.h> 
#include <threadpool.h>
#include <thread_func.h>
#include <fcntl.h>
#include <stdint.h>
#include <messages.h>
#include <lock.h>
#include <files.h>
#include <dirent.h>
#include <string.h>
#include <memory.h>
#include <fcntl.h>


#define SERVER_ADDRESS  "localhost"
#define SERVER_PORT     "8080"
#define BACKLOG         128
#define THREADCOUNT     50
#define BUFF_SIZE       1024
#define PY_STRING_SIZE  2048

#define FILE_DIR "./s_file"
#define TEMP_DIR "./s_temp"
#define PATCH_DIR "./s_patch"
#define PATH_SIZE 64

