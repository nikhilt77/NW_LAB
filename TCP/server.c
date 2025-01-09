
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sock_desc, new_sock, client_len;
    struct sockaddr_in server, client;
    char buffer[1024];


    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    }


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);


    if (bind(sock_desc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Bind failed");
        close(sock_desc);
        exit(1);
    }

    if (listen(sock_desc, 5) == -1) {
        perror("Listen failed");
        close(sock_desc);
        exit(1);
    }

    printf("Server is waiting for connections on port 8080...\n");


    client_len = sizeof(client);
    new_sock = accept(sock_desc, (struct sockaddr *)&client, &client_len);
    if (new_sock == -1) {
        perror("Accept failed");
        close(sock_desc);
        exit(1);
    }

    printf("Connection established.\n");

    int bytes_received = recv(new_sock, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Receiving failed");
    } else {
        buffer[bytes_received] = '\0'; 
        printf("Message from a fellow bro: %s\n", buffer);
    }

    close(new_sock);
    close(sock_desc);

    return 0;
}
