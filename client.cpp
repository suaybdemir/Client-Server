#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    while (true) {
        std::string message;
        std::cout << "You: ";
        std::getline(std::cin, message);
        send(sock, message.c_str(), message.size(), 0);

        memset(buffer, 0, BUFFER_SIZE);
        int bytesRead = read(sock, buffer, BUFFER_SIZE);
        if (bytesRead == 0) {
            std::cout << "Server disconnected" << std::endl;
            break;
        }
        std::cout << "Server: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}

