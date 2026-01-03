#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int PORT = 8080;

void process_client(int client_sock) {
    char buffer[1024] = {0};
    char response[1024] = {0};

    // Receive the client's input
    int r = read(client_sock, buffer, sizeof(buffer));
    buffer[r] = '\0'; // Null-terminate the input

    // Count the number of sentences (based on full stops)
    int sentence_count = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '.') {
            sentence_count++;
        }
    }

    // Prepare the response
    snprintf(response, sizeof(response), "The number of sentences is: %d", sentence_count);

    // Send the response to the client
    send(client_sock, response, strlen(response), 0);

    // Close the connection
    close(client_sock);
    printf("Client disconnected.\n");
}

void start_server() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to IP/port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for clients
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_sock < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        process_client(client_sock);
    }
}

int main() {
    start_server();
    return 0;
}