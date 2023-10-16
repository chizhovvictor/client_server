#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXSIZE 4096

void err(std::string err, int code) {
    std::cout << err.c_str() << std::endl;
    exit(code);
}


int main(int ac, char **av) {

    /* инициализируем переменную для хранения дескриптора созданного сокета, порта */
    int sockfd, portno;             

    struct sockaddr_in servAddr, clientAddr;

    if (ac < 2)
        err("ERROR: no port provided!", 1);

    /* Создание сокета: Вы создаете сокет с 
    использованием функции socket(). Этот сокет будет представлять ваш сервер. */
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        err("ERROR: openning socket!", 1);
    
    /* зачищаем serv_addr от возможного мусора */
    memset(&servAddr, 0, sizeof(servAddr));

    portno = atoi(av[1]);

    /* настраиваем структуру host_addr для использования bind() */

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htonl(portno);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Привязка соксета: С помощью функции bind() вы связываете ваш соксет с определенным 
    IP-адресом и портом на сервере. Это говорит операционной системе, 
    что ваш сервер ожидает входящие соединения на указанном адресе и порту. */

    if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        err("ERROR on binding!", 1);

    /* Установка сокета в режим прослушивания: Далее, с помощью функции listen(), 
    вы говорите серверу начинать прослушивание входящих соединений на этом соксете. 
    Это устанавливает очередь ожидающих соединений. */

    listen(sockfd, 5);

    /* присваиваем длину для accept */
    socklen_t lenClientAddr = sizeof(clientAddr);

    /* Принятие входящих соединений: Когда клиент пытается установить соединение с 
    вашим сервером, сервер использует функцию accept() для принятия входящего соединения. 
    Эта функция создает новый соксет, связанный с клиентским IP-адресом и портом, и использует 
    его для взаимодействия с клиентом. */

    int newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &lenClientAddr);
    if(newsockfd < 0)
        err("ERROR on accept", 1);


    /* Функция inet_ntoa используется для преобразования 32-битного IP-адреса, представленного в 
    формате сетевого порядка байт (big-endian), в строковый формат IP-адреса. */
    std::cout << "Server: got connection from " << inet_ntoa(clientAddr.sin_addr) << "port " << ntohs(clientAddr.sin_port) << std::endl;

    /* Функция send используется для отправки данных через сокет.  */
    send(newsockfd, "Message was gotten!", 19, 0);

    char message[MAXSIZE];
    memset(message, 0, MAXSIZE);

    /* Обработка полученного сообщения с помощью функции  recv */
    int bytes_received = recv(newsockfd, message, sizeof(message), 0);
    if (bytes_received == -1)
        err("ERROR: reading from socket!", 1);
    else if (bytes_received == 0)
        err("The connection was closed by the client", 0);
    else {
        message[bytes_received] = '\0';
        std::cout << "Count of bytes " << bytes_received << ":" << std::endl;
        std::cout << "Message: " << message << std::endl;
    }

    /* обязательно нужно закрывать сокеты после их использования, чтобы избежать 
    утечек ресурсов. Сокеты - это ресурсы операционной системы, и если вы забудете 
    закрыть сокет, это может привести к исчерпанию ресурсов и непредсказуемому 
    поведению вашей программы. */
    
    close(newsockfd);
    close(sockfd);

    /* Закрывайте сокеты после того, как они становятся не нужными, например, 
    когда соединение завершено или когда ваш сервер завершил свою работу. 
    Это хорошая практика для обеспечения корректной работы вашего приложения и 
    избежания ресурсных утечек. */

    return 0;
}