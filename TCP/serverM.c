#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h> // 🔁 Added for handling child cleanup
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd){
    char buff[MAX];
    int n;
    for(;;){
        bzero(buff,MAX);
        read(connfd,buff,sizeof(buff));
        printf("From client: %s\t To client: ",buff);
        bzero(buff,MAX);
        n=0;
        while((buff[n++] = getchar())!='\n');
        write(connfd,buff,sizeof(buff));
        if(strncmp("exit",buff,4)==0){
            printf("Server Exit..\n");
            break;
        }
    }
}

int main(){
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("Socket creation failed\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
        printf("Socket binding failed...\n");
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }

    if((listen(sockfd, 5)) != 0){
        printf("Listen failed..\n");
        exit(0);
    } else
        printf("Server Listening..\n");

    signal(SIGCHLD, SIG_IGN); // 🔁 Prevent zombie processes

    len = sizeof(cli);

    while(1){ // 🔁 Accept multiple clients in a loop
        connfd = accept(sockfd, (SA*)&cli, &len);
        if(connfd < 0){
            printf("Server accept failed..\n");
            continue;
        } else {
            printf("Server accepted a client..\n");
        }

        if(fork() == 0){ // 🔁 Child process handles client
            close(sockfd); // Child doesn't need the listener
            func(connfd);
            close(connfd);
            exit(0);
        } else {
            close(connfd); // Parent doesn't use this socket
        }
    }

    close(sockfd);
}
