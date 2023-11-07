#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main() {
    std::cout << "Start!" << std::endl;

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == sock) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // Create hint structure for the server we are connecting with
    int port = 54000;
    // std::string ipAddress = "0.0.0.0";
    std::string ipAddress = "172.28.0.2";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr *) &hint, sizeof(hint));

    if (-1 == connectRes) {
        std::cerr << "Connection to server failed" << std::endl;
        return -2;
    }

    // While loop
    char buf[4096];
    std::string userInput;

    do {
        std::cout << "> ";
        std::getline(std::cin, userInput);

        // Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);

        if (-1 == sendRes) {
            std::cout << "Sending failed..." << std::endl;
            continue;
        }

        // Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);

        // Display response
        std::cout << bytesReceived << std::endl;
        std::cout << "SERVER: " << std::string(buf, bytesReceived) << std::endl;
    } while (true);

    // Close the socket
    close(sock);

    // Done
    std::cout << "Done!" << std::endl;
    return 0;
}