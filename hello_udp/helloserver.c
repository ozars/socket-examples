#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUFFER_LENGTH (256)

int main()
{
    int sockfd, clifd;
    struct sockaddr_in server_addr, client_addr;
    unsigned int len;
    char mesg[BUFFER_LENGTH];
    int received;
    const int port = 10000;

    // Create socket, AF_INET denotes IP, SOCK_DGRAM denotes UDP
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(-1);
    }

    // Reuse address even if it's used less than about 20 secs ago.
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

    while(1)
    {
        // Receive at most sizeof(mesg) bytes minus one (=BUFFER_LENGTH-1)
        // Minus one is to reserve space for null character ('\0')
        if((received = recvfrom(sockfd, mesg, sizeof(mesg)-1, 0,
                        (struct sockaddr *)&client_addr,
                        &(int){ sizeof(client_addr) })) == -1) {
            perror("recvfrom");
            exit(-1);
        }

        mesg[received] = '\0';

        printf("Received %d bytes from client: %s:%d\n", received,
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        printf("Message: '%s'\n", mesg);
    };
}

