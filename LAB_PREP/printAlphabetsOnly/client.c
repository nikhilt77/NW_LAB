#include<stdio.h>
#include <sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<ctype.h>

#define BUFFER_SIZE 1024

int main(){

    struct sockaddr_in server,client;
    int sendfd,newfd;
    char buffer[BUFFER_SIZE],response[BUFFER_SIZE];
    socklen_t len=sizeof(server);
    sendfd=socket(AF_INET,SOCK_STREAM,0);
    if(sendfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sendfd,(struct sockaddr*)&server,len);

    printf("Enter the string:");
    fgets(buffer,BUFFER_SIZE,stdin);
    send(sendfd,buffer,BUFFER_SIZE,0);

    recv(sendfd,response,BUFFER_SIZE,0);
    printf("%s",response);
    close(sendfd);
}
