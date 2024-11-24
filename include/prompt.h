#ifndef PROMPT_CLIENT
#define PROMPT_CLIENT
#define IP_SIZE 64
void prompt(int connfd);
int parse_input(char* input, int connfd);

#endif