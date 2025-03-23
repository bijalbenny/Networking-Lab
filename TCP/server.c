#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd){
    char buff[MAX];
    int n;
    for(;;){//infinite loop
        bzero(buff,MAX);//clears buffer
        read(connfd,buff,sizeof(buff));
        printf("From client: %s\t To client: ",buff);
        bzero(buff,MAX);
        n=0;
        while((buff[n++] = getchar())!='\n');//copy from buffer
        
        write(connfd,buff,sizeof(buff));
        
        if(strncmp("exit",buff,4)==0){
            printf("Server Exit..\n");
            break;
        }
        
    }
}

int main(){
    int sockfd,connfd,len;
    struct sockaddr_in servaddr,cli;
    
    //socket creation
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        printf("Socket creation failed\n");
        exit(0);
    }
    else{
        printf("Socket successfully created..\n");
    }
        bzero(&servaddr,sizeof(servaddr));
        
        //assign IP,port
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);
        
        //binding socket to ip
        if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0){
            printf("Socket binding failed...\n");
            exit(0);
        }
        else{
            printf("Socket successfully binded..\n");
        }
        //server listening
        if((listen(sockfd,5))!=0){
            printf("Listen failed..\n");
            exit(0);
        }
        else
            printf("Server Listening..\n");
        len = sizeof(cli);
    //accept data from client
    connfd = accept(sockfd,(SA*)&cli,&len);
    if(connfd<0){
        printf("Server accept failed..\n");
        exit(0);
    }
    else
        printf("Server accept the client..\n");
    func(connfd);
    close(sockfd);
}
