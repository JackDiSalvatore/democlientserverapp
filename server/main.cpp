#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <thread>
#include <vector>

class TCPServer {
public:
    TCPServer() : listening(-1) {}

    ~TCPServer() {
        if (listening != -1) {
            close(listening);
        }
    }

    int startServer() {
        std::cout << "Start!" << std::endl;

        // Create listening socket (domain, type, protocol)
        listening = socket(AF_INET, SOCK_STREAM, 0);

        if (-1 == listening) {
            std::cerr << "Cannot create socket";
            return -1;
        }

        // Bind socket to any available IP Address + Port
        struct sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(54000);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

        // Binding Information
        if (-1 == bind(listening, (struct sockaddr*) &hint, sizeof(hint))) {
            std::cerr << "Cannot bind to socket";
            return -2;
        }

        // Mark socket for listening
        if (-1 == listen(listening, SOMAXCONN)) {
            std::cerr << "Cannot listen";
            return -3;
        }

        return 0;
    }

    void runServer() {
        while (true) {
            // Accept an incoming call
            sockaddr_in client;
            socklen_t clientSize = sizeof(client);

            // This is our new "communication" socket
            int clientSocket = accept(listening, (sockaddr*) &client, &clientSize);

            if (-1 == clientSocket) {
                std::cerr << "Problem accepting client";
                continue;
            }

            // Use a separate thread to handle this client
            std::thread clientThread(&TCPServer::handleClient, this, clientSocket);
            clientThread.detach(); // Detach the thread, allowing it to run independently
        }
    }

    void handleClient(int clientSocket) {
        char buf[4096];

        while (true) {
            // Clear buffer
            memset(buf, 0, 4096);

            // Wait for messages
            int bytesRecv = recv(clientSocket, buf, 4096, 0);

            if (-1 == bytesRecv) {
                std::cerr << "There was a connection issue" << std::endl;
                break;
            } else if (0 == bytesRecv) {
                // The client disconnected
                break;
            } else {
                // Display message
                std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;

                // Resend "echo" message
                send(clientSocket, buf, bytesRecv + 1, 0); // "0" for no flags
            }
        }

        // Close client socket
        close(clientSocket);
    }

private:
    int listening;
};

int main() {
    TCPServer server;
    if (server.startServer() == 0) {
        server.runServer();
    }
    return 0;
}
