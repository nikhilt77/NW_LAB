
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sock_desc;
    struct sockaddr_in server, client;
    char buffer[1024];
    socklen_t client_len = sizeof(client);

 
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Server is waiting for messages on port 8080...\n");


    int bytes_received = recvfrom(sock_desc, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &client_len);
    if (bytes_received == -1) {
        perror("Receiving failed");
    } else {
        buffer[bytes_received] = '\0';
        printf("Message from client: %s\n", buffer);
    }


    close(sock_desc);

    return 0;
}
