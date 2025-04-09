#include <netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/_types/_socklen_t.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/time.h>

#define BUFFER_SIZE 1024

int main(){

    int sockfd,newfd;
    socklen_t len;
    struct sockaddr_in server,client;
    char buffer[BUFFER_SIZE];
    int probability=70;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket creation failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0){
        perror("Binding Failed\n");
        exit(0);
    }

    if(listen(sockfd,5)<0){
        perror("Listening Failed\n");
        exit(0);
    }

    len=sizeof(client);
    newfd=accept(sockfd,(struct sockaddr*)&client,&len);
    if(newfd<0){
        perror("Connection Failed\n");
        exit(0);
    }

    int packets=0;
    while(packets<5){
        int packet=recv(newfd,buffer,BUFFER_SIZE,0);
        if(rand()%100 <probability){
            printf("ACK sent for %s\n",buffer);
            send(newfd,"ACK",strlen("ACK"),0);
            packets++;
        }
        else{
            printf("No ACK sent for %s\n",buffer);
        }
        memset(buffer,0,BUFFER_SIZE);
    }
    close(sockfd);
    close(newfd);
}
