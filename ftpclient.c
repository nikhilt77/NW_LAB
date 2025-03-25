#include <netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    client_socket=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(PORT);

    if(connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("Connection Failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter file to request:");
    scanf("%s",input);

    printf("Requesting File....!\n");
    send(client_socket,input,strlen(input),0);

    while(recv(client_socket,buffer,BUFFER_SIZE,0)>0){
        printf("%s",buffer);
        memset(buffer,0,BUFFER_SIZE);
    }
    printf("\n");
    close(client_socket);
}
