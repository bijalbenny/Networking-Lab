#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define MAX 100
#define PORT 8080
#define SA struct sockaddr

int main() {
    FILE *fp;
    int sockfd, connfd, len;
    char rcv[MAX], fileread[MAX];
    struct sockaddr_in servaddr, cli;

    // Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    
    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket binding failed...\n");
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }
    
    // Listen
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed..\n");
        exit(0);
    } else {
        printf("Server Listening..\n");
    }
    
    len = sizeof(cli);
    
    // Accept connection
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed..\n");
        exit(0);
    } else {
        printf("Server accepted the client..\n");
    }

    // Receive filename from client
    int n = recv(connfd, rcv, MAX, 0);
    rcv[n] = '\0';

    fp = fopen(rcv, "r");
    if (fp == NULL) {
        send(connfd, "error", 5, 0);
        close(connfd);
    } else {
        while (fgets(fileread, sizeof(fileread), fp)) {
            if (send(connfd, fileread, sizeof(fileread), 0) < 0) {
                printf("Can’t send file contents\n");
            }
            sleep(1);
        }
        send(connfd, "completed", 10, 0);
    }
    
    fclose(fp);
    close(sockfd);
    return 0;
}
