#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define MAXSIZE 4096

void err(std::string err, int code) {
    std::cout << err << std::endl;
    exit(code);
}

int main(int ac, char **av) {

    int sockfd;
    struct sockaddr_in servAddr;

    std::string address = "127.0.0.1";

    int portno = atoi(av[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        err("ERROR: openning socket!", 1);

    memset(&servAddr, 0, sizeof(servAddr));
    
    if (inet_addr(address.c_str()) == -1) {
        struct hostent *server = gethostbyname(address.c_str());
        struct in_addr **tmp; 
        if(server == NULL)
            err("ERROR: Failed to resolve hostname!", 1);

        tmp = (struct in_addr **)server->h_addr_list;
            for (int i = 0; tmp[i] != NULL; ++i) {
                servAddr.sin_addr = *tmp[i];
                break;
        }
    } else {
        servAddr.sin_addr.s_addr = inet_addr(address.c_str());
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        err("ERROR connecting!", 1);

    std::cout << "Please enter the message: " << std::endl;

    char message[MAXSIZE];
    memset(message, 0, MAXSIZE);

     /* Обработка полученного сообщения с помощью функции  recv */

    // int bytes_received = recv(sockfd, message, sizeof(message), 0);
    // if (bytes_received == -1)
    //     err("ERROR: reading from socket!", 1);
    // else if (bytes_received == 0)
    //     err("The connection was closed by the client", 0);
    // else {
    //     message[bytes_received] = '\0';
    //     std::cout << "Count of bytes " << bytes_received << ":" << std::endl;
    //     std::cout << "Message: " << message << std::endl;
    // }

    fgets(message, MAXSIZE, stdin);
    int n = write(sockfd, message, strlen(message));
    if (n < 0) 
         err("ERROR writing to socket", 1);
    bzero(message, MAXSIZE);
    n = read(sockfd, message, MAXSIZE - 1);
    if (n < 0) 
         err("ERROR reading from socket", 1);
    printf("%s\n", message);

    close(sockfd);
    return 0;
}