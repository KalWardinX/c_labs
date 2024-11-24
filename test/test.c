#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


int main() {
    const char *hostname = "localhost";
    const char *port = "8080";  // Specify the port as a string
    struct addrinfo hints, *res;
    int status;

    // Zero out the hints structure and set options
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;        // Use AF_INET for IPv4
    hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets

    // Get address information
    status = getaddrinfo(hostname, port, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // Print the IP address and port
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(res->ai_family, &(ipv4->sin_addr), ipstr, sizeof ipstr);
    printf("Address: %s\n", ipstr);
    printf("Port: %d\n", ntohs(ipv4->sin_port));

    // Free the linked list
    freeaddrinfo(res);

    return 0;
}
