#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
    struct sockaddr_in server;
    int sockfd;
    socklen_t len=sizeof(server);
    char buffer[1024];
    char response[1024];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    printf("Enter message:");
    fgets(buffer,sizeof(buffer),stdin);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&server,len);
    printf("Message sent to server\n");

    recvfrom(sockfd,response,strlen(response),0,(struct sockaddr*)&server,&len);
    printf("Server Connected:%s\n",response);

    close(sockfd);
}
