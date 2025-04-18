#include <netinet/in.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 1024
#define MAX 20

int main(){

    int sockfd,clientfd;
    struct sockaddr_in server,client;
    socklen_t len;
    int rows,columns;
    char buffer[BUFFER_SIZE];
    int matrix1[MAX][MAX],matrix2[MAX][MAX];

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket Creation Failed\n");
        exit(0);
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    if((bind(sockfd,(struct sockaddr*)&server,sizeof(server)))<0){
        perror("Bind Failed\n");
        exit(0);
    }

    if((listen(sockfd,5))<0){
        perror("Listening Failed\n");
        exit(0);
    }

    len=sizeof(client);
    clientfd=accept(sockfd,(struct sockaddr*)&client,&len);
    if(clientfd<0){
        perror("Listening socket not created\n");
        exit(0);
    }

    recv(clientfd,&rows,sizeof(int),0);
    recv(clientfd,&columns,sizeof(int),0);


    printf("Receiving Matrix \n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            recv(clientfd,&matrix1[i][j],sizeof(int),0);
        }
    }
    // printf("Receiving Matrix 2\n");
    // for(int i=0;i<rows;i++){
    //     for(int j=0;j<columns;j++){
    //         recv(clientfd,&matrix2[i][j],sizeof(int),0);
    //     }
    // }

    int isZero=1;
    int isOne=1;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(i==j&&matrix1[i][j]!=1){
                isOne=0;
            }
            if(i!=j&&matrix1[i][j]!=0){
                isZero=0;
            }
        }
    }

    char positive[BUFFER_SIZE],negative[BUFFER_SIZE];
    strcpy(positive,"The Matrix is Identity");
    strcpy(negative,"The Matrices is not Identity");

    if(isZero  && isOne){
        send(clientfd,positive,strlen(positive),0);
    }
    else{
        send(clientfd,negative,strlen(negative),0);
    }

    close(clientfd);
    close(sockfd);
}
