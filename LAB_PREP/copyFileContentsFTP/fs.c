#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/file.h>

#define BUFFER_SIZE 1024

int main(){
    int sockfd,newfd;
    socklen_t len;
    struct sockaddr_in server,client;
    char buffer[BUFFER_SIZE],filename[BUFFER_SIZE],file[BUFFER_SIZE],response[BUFFER_SIZE];

    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Socket Creation Failed\n");
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

    if(recv(newfd,filename,BUFFER_SIZE,0)<0){
        perror("Failed to obtain file name\n");
        exit(0);
    }
    printf("Filename:%s\n",filename);

    FILE* fr=fopen("copy.txt","w");
    FILE* f=fopen(filename,"r");
    if(f==NULL){
        perror("Failed to open file\n");
        sprintf(buffer,"Failed to open file:%s\n",filename);
        send(newfd,buffer,strlen(buffer),0);
        memset(buffer,0,BUFFER_SIZE);
        exit(0);
    }
    else{
        while(fgets(file,BUFFER_SIZE,f)!=NULL){
            send(newfd,file,strlen(file),0);
            fputs(file,fr);
            printf("%s",file);
            memset(file,0,BUFFER_SIZE);
        }
    }
    close(sockfd);
    close(newfd);
}
