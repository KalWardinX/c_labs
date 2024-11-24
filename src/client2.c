#include <client.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc != 4){
        printf("Usage: %s <server_ip> <server_port> <iter>", argv[0]);
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
    srand(time(NULL));
    if (connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0){
        fprintf(stderr, "Error(%d):= client.c -> main(connect) %s\n", errno, strerror(errno));
        exit(1);
    }

    char* commands[5] = {"read","run","run","run","run" };
    char* __files[4] = {"hello.py", "worldpeace.py", "touch.py", "new.py"};
    int iter = atoi(argv[3]);
    iter = 1;
    char request[20];
    // sprintf(request,"echo request iter %d >> result2.txt", iter);
    // system(request);
    // system("date +%s >> result2.txt");
    while(iter--){

        int cmd = rand()%5;
        int f = rand()%4;
        if(strcmp("list", commands[0]) == 0){
            parse_input("list", sock);
            // sleep(rand()%5 + 5);
        }
        else{
            char com[CMD_SIZE];
            sprintf(com, "%s %s", commands[0], __files[2]);
            parse_input(com, sock);
            // sleep(rand()%2 + 5);
        }
    }
    
    parse_input("exit", sock);
    // system("date +%s >> result2.txt");

    close(sock);
    return 0;
}