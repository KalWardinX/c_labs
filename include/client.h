#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h> // contains addrinfo and getaddrinfo
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <messages.h>
#include <string.h>
#include <prompt.h>
#include <unistd.h>
#include <client_func.h>

#define READ_DIR "read/"
#define WRITE_DIR "write/"
#define PATCH_DIR "patch/"
#define TEMP_DIR "c_temp/"
#define CMD_SIZE 128
#define BUFFER_SIZE 512