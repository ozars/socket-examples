#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int sockfd, clifd;
    struct sockaddr_in server_addr, client_addr;
    unsigned int len;
    char mesg[] = "HELLO";
    int sent;
    const int port = 10000;

    // Create socket, AF_INET denotes IP, SOCK_STREAM denotes TCP
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(-1);
    }

    // Reuse address even if it's used less than 240 secs (default value) ago.
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int) { 1 },
            sizeof(int)) == -1) {
        perror("setsockopt");
        exit(-1);
    }

    // Set server address options to be used in bind call

    // Address family type is AF_INET (i.e. Internet, IPv4)
    server_addr.sin_family = AF_INET;

    // Set port number (htons converts byte order for port to network order)
    server_addr.sin_port = htons(port);

    // Receive connections from any interface of this machine
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Alternatively, only from localhost (loopback interface)
    /* server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); */

    // Set the rest to zero
    memset(&server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));

    len = sizeof(struct sockaddr_in);

    // Bind using server
    if((bind(sockfd, (struct sockaddr *)&server_addr, len)) == -1)
    {
        perror("bind");
        exit(-1);
    }

    // Listen bound socket, with backlog = 5
    if((listen(sockfd, 5)) == -1)
    {
        perror("listen");
        exit(-1);
    }

    while(1)
    {
        // Accept a client
        if((clifd = accept(sockfd, (struct sockaddr *)&client_addr,
                        &len)) == -1)
        {
            perror("accept");
            exit(-1);
        }

        // Send message to accepted client
        if((sent = send(clifd, mesg, strlen(mesg), 0)) == -1) {
            perror("send");
            exit(-1);
        }

        printf("Sent %d bytes to client: %s:%d\n", sent,
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Close connection to the client
        close(clifd);
    }
}

