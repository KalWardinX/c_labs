#include <client.h>

void prompt(int connfd){
    char* prompt = "C*_Labs > ";
    while(1){
        write(STDOUT_FILENO, prompt, 11);
        char input[IP_SIZE] = {'\0'};
        int rd = read(STDIN_FILENO, input, IP_SIZE);
        // printf("input = %s\n", input);
        // fflush(stdout);
        int ret = parse_input(input, connfd);
        if(ret == 1){
            break;
        }
    }
}


int parse_input(char* input, int connfd){
    char* token = "";
    // printf("parseinput = %s\n", input);
        // fflush(stdout);
    token = strtok(input, " \n\0");

    if( strcmp(token, "list") == 0 ){
        c_list_files(connfd);
    }
    else if( strcmp(token, "read") == 0 ){
        token = strtok(0, " \n\0");
        // printf("input %s, token %s\n", input, token);
        // fflush(stdout);
        c_read_file(connfd, token);
    }
    else if( strcmp(token, "write") == 0 ){
        token = strtok(0, " \n\0");
        c_write_file(connfd, token);
    }
    else if( strcmp(token, "run") == 0 ){
        token = strtok(0, " \n\0");
        c_run_file(connfd, token);
    }
    else if( strcmp(token, "del") == 0 ){
        token = strtok(0, " \n\0");
        c_del_file(connfd, token);
    }
    else if( strcmp(token, "exit") == 0){
        c_exit(connfd);
        return 1;
    }
    else if( strcmp(token, "help") == 0 ){
        c_help();
    }
    else{
        write(STDERR_FILENO, "Invalid command, type 'help to know more\n", sizeof("Invalid command, type 'help to know more\n"));
    }
    return 0;
}

