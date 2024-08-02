#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE] = {0};
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
        if (bytesRead == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        std::cout << "Client: " << buffer << std::endl;
        std::string message;
        std::getline(std::cin, message);
        send(clientSocket, message.c_str(), message.size(), 0);
    }
    close(clientSocket);
}

int main() {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set the SO_REUSEADDR socket option
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverFd, 3) < 0) {
        perror("listen failed");
        close(serverFd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        // Accept an incoming connection
        if ((newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            close(serverFd);
            exit(EXIT_FAILURE);
        }

        std::cout << "Connection established with client" << std::endl;
        handleClient(newSocket);
    }

    close(serverFd);
    return 0;
}

