
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sock_desc;
    struct sockaddr_in server;
    char message[] = "Hola..!";

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    }


    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 


    if (connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Connection failed");
        close(sock_desc);
        exit(1);
    }

    printf("Connected to the server.\n");

    if (send(sock_desc, message, strlen(message), 0) == -1) {
        perror("Send failed");
        close(sock_desc);
        exit(1);
    }

    printf("Bruh who are you?: %s\n", message);


    close(sock_desc);

    return 0;
}
