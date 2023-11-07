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

    // Create listening socket (domain, type, protocol)
    int listening = socket(AF_INET, SOCK_STREAM, 0);

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
    if (-1 == bind(listening, (struct sockaddr *) &hint, sizeof(hint))) {
        std::cerr << "Cannot bind to socket";
        return -2;
    }

    // Mark socket for listening
    if (-1 == listen(listening, SOMAXCONN)) {
        std::cerr << "Cannot listen";
        return -3;
    }

    // Accept an incoming call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    // This is our new "communication" socket
    int clientSocket = accept(listening, (sockaddr*) &client, &clientSize);

    if (-1 == clientSocket) {
        std::cerr << "Problem accepting client";
        return -4;
    }

    // Close the listening socket
    close(listening);

    // Clean up memory
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    // Get host machine name
    int result = getnameinfo((sockaddr *) &client, clientSize, host, NI_MAXHOST, service, NI_MAXSERV, 0);

    if (result) {
        std::cout << host << " connected on " << service << std::endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;
    }

    // Receive messages
    char buf[4096];
    while (true) {
        // Clear buffer
        memset(buf, 0, 4096);

        // Wait for messages
        int bytesRecv = recv(clientSocket, buf, 4096, 0);   // "0" for no flags
        
        if (-1 == bytesRecv) {
            std::cerr << "There was a connection issue" << std::endl;
        } else if (0 == bytesRecv) {
            // cerr << "The client disconnected" << endl;
            0;
        } else {
            // Display message
            std::cout << bytesRecv << std::endl;
            std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;

            // Resend "echo" message
            send(clientSocket, buf, bytesRecv + 1, 0);  // "0" for no flags
        }
    }

    // Close client socket
    close(clientSocket);

    // Done
    std::cout << "Done!" << std::endl;
    return 0;
}