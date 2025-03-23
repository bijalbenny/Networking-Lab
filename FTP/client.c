#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define MAX 100
#define PORT 8080
#define SA struct sockaddr

int main() {
    FILE *fp;
    int sockfd, s;
    char name[MAX], rcvg[MAX], fname[MAX];
    struct sockaddr_in servaddr;

    // Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed..\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }
    
    bzero(&servaddr, sizeof(servaddr));
    
    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    // Connect to server
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed..\n");
        exit(0);
    } else {
        printf("Connected to the server..\n");
    }

    // Get filenames
    printf("Enter the existing file name: ");
    scanf("%s", name);
    printf("Enter the new file name: ");
    scanf("%s", fname);
    
    fp = fopen(fname, "w");
    send(sockfd, name, sizeof(name), 0);

    while (1) {
        s = recv(sockfd, rcvg, MAX, 0);
        rcvg[s] = '\0';

        if (strcmp(rcvg, "error") == 0) {
            printf("File is not available\n");
            break;
        }

        if (strcmp(rcvg, "completed") == 0) {
            printf("File is transferred........\n");
            break;
        } else {
            fputs(rcvg, fp);
            fputs(rcvg, stdout);
        }
    }

    fclose(fp);
    close(sockfd);
    return 0;
}
