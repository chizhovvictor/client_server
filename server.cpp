#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

void err(std::string err, int code) {
    std::cout << err.c_str() << std::endl;
    exit(code);
}


int main(int ac, char **av) {

    // инициализируем переменную для хранения дескриптора созданного сокета, порта
    int sockfd, portno;             

    struct sockaddr_in servAddr, clientAddr;

    if (ac < 2)
        err("ERROR: no port provided!", 1);

    // создаем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        err("ERROR: openning socket!", 1);
    
    //зачищаем serv_addr от возможного мусора
    memset(&servAddr, 0, sizeof(servAddr));

    portno = atoi(av[1]);

    // настраиваем структуру host_addr для использования bind()

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htonl(portno);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //привязываем нашу абстракцию сокет по фд к данным компютера порта и ip
    if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        err("ERROR on binding!", 1);

    /* устанавливаем количество клиентов, которые могут подключиться. Если количество клиентов, ожидающих соединение, превышает это значение, то они получат сообщение о том, что сервер переполнен или занят. */

    listen(sockfd, 5);



    
    




    



    return 0;
}