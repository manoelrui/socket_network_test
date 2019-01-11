#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char** argv) {
    int sockfd, newsockfd, port, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        cerr << "Error, no port provided" << endl;
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "ERROR opening socket" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr));

    port = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "ERROR on binding" << endl;
        return -1;
    }

    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
    if(newsockfd < 0) {
        cerr << "ERROR on accept" << endl;
        return -1;
    }

    memset(&buffer, 0, sizeof(buffer));
    do {
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            cerr << "ERROR reading from socket" << endl;
            return -1;
        } else if (n == 0) {
            cout << "End of reception" << endl;
        } else {
            cerr << "Error to receive bytes" << endl;
            return -1;
        }

    } while(n > 0);

	return 0;
}
