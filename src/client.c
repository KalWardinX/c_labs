#include <client.h>


int main(int argc, char** argv){
    if (argc != 3){
        printf("Usage: %s <server_ip> <server_port>", argv[0]);
        exit(1);
    }

    char *serv_addr = argv[1];
    int port = atoi(argv[2]);

// networking SETUP
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Error(%d):= server.c -> main(socket) %s\n", errno, strerror(errno));
        exit(1);
    }

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serv_addr, &serv.sin_addr) <= 0)
    {
        fprintf(stderr,"Error(%d) := client.c -> main(inet_pton) %s\n", errno, strerror(errno));
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0){
        fprintf(stderr, "Error(%d):= client.c -> main(connect) %s\n", errno, strerror(errno));
        exit(1);
    }

    prompt(sock);

    close(sock);
    return 0;
}