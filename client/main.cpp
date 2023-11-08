#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

class TCPClient {
public:
    TCPClient() : sock(-1) {}

    ~TCPClient() {
        if (sock != -1) {
            close(sock);
        }
    }

    int connectServer(const std::string& ipAddress, int port) {
        std::cout << "Start!" << std::endl;

        // Create a socket
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (-1 == sock) {
            std::cerr << "Error creating socket" << std::endl;
            return -1;
        }

        // Create hint structure for the server we are connecting with
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

        // Connect to the server on the socket
        int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

        if (-1 == connectRes) {
            std::cerr << "Connection to server failed" << std::endl;
            return -2;
        }

        return 0;
    }

    void runClient() {
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
            std::cout << "SERVER: " << std::string(buf, bytesReceived) << std::endl;
        } while (true);
    }

private:
    int sock;
};

int main() {
    TCPClient client;
    if (client.connectServer("172.28.0.2", 54000) == 0) {
        client.runClient();
    }
    return 0;
}
