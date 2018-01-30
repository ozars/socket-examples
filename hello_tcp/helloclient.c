#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUFFER_LENGTH 256

int main()
{
	int sockfd;
	struct sockaddr_in server_addr;
	unsigned int len;
	char mesg[BUFFER_LENGTH];
	int received;
	const int port = 10000;

    // Create socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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

	len = sizeof(struct sockaddr_in);

    // Connect to server
    if(connect(sockfd, (struct sockaddr *)&server_addr, len) == -1)
    {
        perror("connect");
        exit(-1);
    }

    do
	{
        // Receive at most sizeof(mesg) bytes minus one (=BUFFER_LENGTH-1)
        // Minus one is to reserve space for null character ('\0')
        if((received = recv(sockfd, mesg, sizeof(mesg)-1, 0)) == -1) {
            perror("recv");
            exit(-1);
        }

        mesg[received] = '\0';

        printf("Received %d bytes from server: %s:%d\n", received,
            inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

        printf("Message: '%s'\n", mesg);

        // If received = 0 that means server closed the connection
	} while(received != 0);

    close(sockfd);
}
