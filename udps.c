#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    struct sockaddr_in server,client;
    int sockfd,newsock;
    socklen_t len=sizeof(client);
    char buffer[1024];

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    //listen(sockfd,5);
    //newsock=accept(sockfd,(struct sockaddr*)&client,&len);
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&client,&len);
    printf("Connection Done:%s\n",buffer);
    sendto(sockfd,"The server is speaking:",20,0,(struct sockaddr*)&client,len);

    close(newsock);
    close(sockfd);
}
