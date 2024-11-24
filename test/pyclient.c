#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <server_ip> <server_port>", argv[0]);
        return -1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);


    int sock, ret;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
    {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed\n");
        return -1;
    }

    char message[2048] = {0};
    // char buffer[256] = {0};
    while(1){
        memset(message, 0, sizeof(message));
        int read_bytes = read(STDIN_FILENO, buffer, 256);
    int k=0;
    while(read_bytes){
        strncpy(message+k, buffer, read_bytes);
        memset(buffer, 0,BUF_SIZE);
        k+=read_bytes;
        read_bytes = read(STDIN_FILENO, buffer, 256);
    }
    ret = send(sock, message, strlen(message), 0);
    if (ret == -1)
    {
        printf("Failed to send message\n");
        return -1;
    }
    printf("Sent: %s\n", message);

    ret = recv(sock, buffer, BUF_SIZE, 0);
    if (ret == -1)
    {
        printf("Failed to receive message\n");
        return -1;
    }
    printf("Received: %s\n", buffer);
    }
    

    close(sock);

    return 0;
}
