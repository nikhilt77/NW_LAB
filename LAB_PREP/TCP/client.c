//chat application using tcp that exits on a message STOP


#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024

int main(){
    int clientfd;
    struct sockaddr_in server;
    socklen_t client;
    char buffer[BUFFER_SIZE];

    clientfd=socket(AF_INET,SOCK_STREAM,0);
    if(clientfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    if((connect(clientfd,(struct sockaddr*)&server,sizeof(server)))){
        perror("No connection done\n");
        exit(0);
    }
    while(1){
        memset(buffer, 0, BUFFER_SIZE);
        read(clientfd,buffer,BUFFER_SIZE);
        if(strncmp(buffer,"STOP",4)==0){
            printf("Closing Connection...\n");
            close(clientfd);
            break;
        }
        printf("Server:%s\n",buffer);
        printf("Enter Message:");
        fgets(buffer,BUFFER_SIZE,stdin);
        send(clientfd,buffer,BUFFER_SIZE,0);
        printf("Message sent to Server\n");
    }
}
