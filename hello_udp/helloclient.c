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
    int sockfd;
    struct sockaddr_in server_addr;
    unsigned int len;
    char mesg[] = "HELLO";
    int sent;
    const int port = 10000;

    // Create socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(-1);
    }

    // Set server address options to be used in connect call

    // Address family type is AF_INET (i.e. Internet, IPv4)
    server_addr.sin_family = AF_INET;

    // Set port number (htons converts byte order for port to network order)
    server_addr.sin_port = htons(port);

    // Connect to localhost IP
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Set the rest to zero
    memset(&server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));

    // Send message to server
    if((sent = sendto(sockfd, mesg, strlen(mesg), 0,
                    (struct sockaddr *)&server_addr,
                    sizeof(server_addr))) == -1) {
        perror("sendto");
        exit(-1);
    }

    printf("Sent %d bytes to server: %s:%d\n", sent,
        inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    close(sockfd);
}
