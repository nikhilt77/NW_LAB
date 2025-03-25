#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server;
    int sockfd;
    char buffer[1024];
    printf("Enter the message to send to server:");
    fgets(buffer,sizeof(buffer),stdin);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);
    connect(sockfd,(struct sockaddr*)&server,sizeof(server));
    send(sockfd,buffer,strlen(buffer),0);
    read(sockfd,buffer,sizeof(buffer));
    printf("Acceptance from Server:%s\n",buffer);

    close(sockfd);
}
