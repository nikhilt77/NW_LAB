//chat application using tcp that exits on a message STOP

#include<stdio.h>
#include <sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 1024

int main(){

    struct sockaddr_in server,client;
    int sendfd,newfd;
    socklen_t len=sizeof(client);
    char buffer[BUFFER_SIZE];

    sendfd=socket(AF_INET,SOCK_STREAM,0);
    if(sendfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    if((bind(sendfd,(struct sockaddr*)&server,sizeof(server))<0)){
        perror("Binding Failed\n");
        exit(0);
    }

    if(listen(sendfd,5)<0){
        perror("No one to listen to\n");
        exit(0);
    }

    newfd=accept(sendfd,(struct sockaddr*)&client,&len);
    if(newfd<0){
        perror("Error creating the receiver socket\n");
        exit(0);
    }
    while(1){
        memset(buffer,0,BUFFER_SIZE);
        printf("Enter the message:");
        fgets(buffer,BUFFER_SIZE,stdin);
        if(strncmp(buffer,"STOP",4)==0){
            send(newfd,buffer,strlen(buffer),0);
            close(newfd);
            close(sendfd);
            break;
        }
        send(newfd,buffer,strlen(buffer),0);
        printf("Connection Established\n");
        printf("Message from client\n");
        read(newfd,buffer,BUFFER_SIZE);
        printf("Client:%s\n",buffer);
    }
}
