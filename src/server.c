#include <c_labs.h>

files* files_list;

/*================================*/
        /* Main funciton */ 
/*================================*/

int main( int argc, char** argv ){
    char command[256];
    sprintf(command, "mkdir -p %s", FILE_DIR);
    system(command);
    sprintf(command, "mkdir -p %s", TEMP_DIR);
    system(command);
    sprintf(command, "mkdir -p %s", PATCH_DIR);
    system(command);
// Validate Arguments
    if( (argc < 2 || argc > 5) || (strcmp(argv[1], "help")==0 || (strcmp(argv[1], "run")!=0)) ){
        fprintf(stdout, "Usage: %s option [Server Address] [Port Number] [Thread Count]\n", argv[0]);
        fprintf(stdout, "\toption :\n");
        fprintf(stdout, "\t\thelp : display this help\n");
        fprintf(stdout, "\t\trun  : runs the server\n");
        exit(1);
    }

// Parse Arguments
    char* serv_addr = SERVER_ADDRESS;
    char* port      = SERVER_PORT ;
    int thread_cnt  = THREADCOUNT;
    if(argc == 3){
        thread_cnt = atoi(argv[2]);
    }
    else if(argc == 4){
        serv_addr = argv[2];
        port = argv[3] ;
    }
    else if(argc == 5){
        serv_addr = argv[2];
        port = argv[3] ;
        thread_cnt = atoi(argv[4]);
    }
    
        // test args
        {
            // fprintf(stdout, "addr: %s, port: %s, threads: %d\n", serv_addr, port, thread_cnt);
        }

// Initialize python interpreter
    // Py_Initialize();


// init files
    files_list = init_files(256);
    first_init(files_list);
// Create connnection queue
    conn_queue *cq = conn_queue_init();

// Create Threadpool
    threadpool* tp = threadpool_init(thread_cnt);
    // assign function to threads in threadpool
    args arg = {.cq = cq, .tp = tp};
    if(threadpool_assign_func(tp, &thread_func, &arg)){
        fprintf(stderr, "Error:= server.c -> threadpool_assign_func.\n");
        exit(1);
    }


// networking SETUP
    // addrinfo struct setup
    struct addrinfo hints, *res;
    bzero( &hints, sizeof(struct addrinfo) );
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = SOCK_STREAM;
    
    int r_getaddrinfo;
    if ((r_getaddrinfo = getaddrinfo(serv_addr, port, &hints, &res)) != 0){
        fprintf(stderr, "Error(%d):= server.c -> main(getaddrinfo) %s\n", r_getaddrinfo, gai_strerror(r_getaddrinfo));
        exit(1);
    }
        // test getaddrinfo
        {
            fprintf(stdout, "getaddrinfo: %d\n", r_getaddrinfo);
            fprintf(stdout, "Addr info: ");
            struct sockaddr_in* s = (struct sockaddr_in*)res->ai_addr;
            char addr[20];
            inet_ntop(AF_INET, &s->sin_addr.s_addr,addr, res->ai_addrlen);
            fprintf(stdout, "addr: %s:%d\n", addr, ntohs(s->sin_port));
        }
    // socket
    int listen_fd;
    if( ( listen_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol) ) < 0 ){
        fprintf(stderr, "Error(%d):= server.c -> main(socket) %s\n", errno, strerror(errno));
        exit(1);
    }
        // test socket
        {
            fprintf(stdout, "Listen FD: %d\n", listen_fd);
        }

    // bind
    int r_bind = 0;
    if( (r_bind = bind(listen_fd, res->ai_addr, res->ai_addrlen)) == -1 ){
        fprintf(stderr, "Error(%d):= server.c -> main(bind) %s\n", errno, strerror(errno));
        exit(1);
    }
        // test bind
        {
            fprintf(stdout, "Bind: %d\n", r_bind);
        }
    
    // listen
    int r_listen = 0;
    if( (r_listen = listen(listen_fd, BACKLOG)) == -1 ){
        fprintf(stderr, "Error(%d):= server.c -> main(listen) %s\n", errno, strerror(errno));
        exit(1);
    }
        // test listen
        {
            fprintf(stdout, "Listen: %d\n", r_listen);
        }
    
    // connect
    while(1){
        struct sockaddr_in *client = NULL;
        int conn_fd = 0;
        if( (conn_fd = accept(listen_fd, (struct sockaddr*)client, &res->ai_addrlen)) == -1 ){
            fprintf(stderr, "Error(%d):= server.c -> main(accept) connection failed: %s\n", errno, strerror(errno));
            continue;
        }
        enqueue(cq, conn_fd);
        thread_awake(tp);
    }

// Wait for threads
    threadpool_join(tp);

//  Close python interpreter
    // Py_Finalize();m
    // char command[256];
    sprintf(command, "rmdir -rf %s", TEMP_DIR);
    system(command);
    sprintf(command, "rmdir -rf %s", PATCH_DIR);
    system(command);
    return EXIT_SUCCESS;
}