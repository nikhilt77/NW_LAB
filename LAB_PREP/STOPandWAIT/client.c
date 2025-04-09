#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<time.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024

int main(){

    int sockfd;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(server);
    char buffer[BUFFER_SIZE];
    char Packet[50];
    struct timeval tv;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    len=sizeof(server);
    connect(sockfd,(struct sockaddr*)&server,len);

    tv.tv_sec=3;
    tv.tv_usec=0;
    setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(const char*)&tv,sizeof(tv));

    int packets=0;
    while(packets<5){
        sprintf(Packet,"Packet - %d",packets);
        send(sockfd,Packet,strlen(Packet),0);
        int res=recv(sockfd,buffer,BUFFER_SIZE,0);
        printf("Sending %s\n",Packet);
        if(res<0){
            perror("No response received\n");
            printf("No ACK received for %s\nRetransmitting...",Packet);
        }
        else if(strcmp(buffer,"ACK")==0){
            printf("ACK received for %s\n",Packet);
            packets++;
        }
        memset(buffer,0,BUFFER_SIZE);
    }
    close(sockfd);
}
