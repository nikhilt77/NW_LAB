#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 1024
#define PORT 8080

void handleClient(int client_socket){

    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    int bytesReceived=recv(client_socket,filename,BUFFER_SIZE,0);

    if(bytesReceived<0){
        perror("File not received\n");
        close(client_socket);
        return;
    }

    FILE* file=fopen(filename,"r");
    if(file==NULL){
        char* errorMessage="Failed to load file";
        send(client_socket,errorMessage,strlen(errorMessage),0);
        perror("File not found\n");
        return;
    }
    else{
        while(fgets(buffer,BUFFER_SIZE,file)!=NULL){
            send(client_socket,buffer,BUFFER_SIZE,0);
            memset(buffer,0,BUFFER_SIZE);
        }

        printf("File sent to client\n");
        fclose(file);
    }
    close(client_socket);
}

int main(){
    struct sockaddr_in server_addr,client_addr;
    int server_socket,client_socket;
    socklen_t len=sizeof(client_addr);

    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket<0){
        perror("Server socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(PORT);

    if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("Binding Failed\n");
        exit(EXIT_FAILURE);
    }

    if(listen(server_socket,3)<0){
        perror("Listening Rejected\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&len);
        if(client_socket<0){
            perror("Failed to accept the client\n");
            exit(EXIT_FAILURE);
        }
        handleClient(client_socket);
    }
    close(server_socket);
}
