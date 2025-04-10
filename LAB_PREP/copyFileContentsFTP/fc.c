#include <netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define BUFFER_SIZE 1024

int main(){

    int sockfd;
    socklen_t len;
    struct sockaddr_in server,client;
    char buffer[BUFFER_SIZE],filename[BUFFER_SIZE];

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sockfd,(struct sockaddr*)&server,sizeof(server));

    printf("Enter filename:");
    fgets(filename,BUFFER_SIZE,stdin);
    send(sockfd,filename,strlen(filename)-1,0);

    recv(sockfd,buffer,BUFFER_SIZE,0);
    printf("%s",buffer);
    close(sockfd);
}
