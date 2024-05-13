#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

// Прототип функции, обслуживающей подключившихся пользователей
void dostuff(int);

// Функция обработки ошибок
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// количество активных пользователей 
int nclients = 0;

// Макрос для печати количества активных пользователей 
void printusers()
{ 
    if(nclients)
        printf("%d user(s) online\n", nclients);
    else
        printf("No users online\n");
}



int main(int argc, char *argv[])
{
    printf("TCP SERVER DEMO\n");
    
    int sockfd, newsockfd; // Дескрипторы сокетов
    int portno; // Номер порта
    int pid; // ID номер потока
    socklen_t clilen; // Размер адреса клиента типа socklen_t
    struct sockaddr_in serv_addr, cli_addr; // Структура сокета сервера и клиента
    
    // Ошибка, если не указан порт
    if (argc < 2) 
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    
    // Шаг 1 - создание сокета
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Ошибка при создании сокета
    if (sockfd < 0) 
       error("ERROR opening socket");
    
    // Шаг 2 - связывание сокета с локальным адресом
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Сервер принимает подключения на все IP-адреса
    serv_addr.sin_port = htons(portno);
    
    // Вызываем bind для связывания
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    
    // Шаг 3 - ожидание подключений, размер очереди - 5
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    
    // Шаг 4 - извлекаем сообщение из очереди
    // Цикл извлечения запросов на подключение из очереди    
    while (1) 
    {
         newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
        nclients++; // Увеличиваем счетчик подключившихся клиентов
        
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)  
        {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else close(newsockfd);
     } /* end of while */
     close(sockfd);
     return 0; /* We never get here */
}

void dostuff(int sock)
{
    int bytes_recv; // Размер принятого сообщения
    int a, b, result; // Переменные для операндов и результата
    char op_str[20]; // Строка для хранения операции
    
    char buff[1024];
    // Отправляем клиенту приветственное сообщение
    const char* welcome_msg = "Welcome! Please specify your operation and two numbers separated by spaces (e.g., add 5 3).\n";
    write(sock, welcome_msg, strlen(welcome_msg));
    
    // Получаем сообщение от клиента
    bytes_recv = read(sock, buff, sizeof(buff) - 1);
    if (bytes_recv < 0)
        error("ERROR reading from socket");
    buff[bytes_recv] = '\0';
    
    // Разбираем строку, чтобы получить операцию и операнды
    sscanf(buff, "%s %d %d", op_str, &a, &b);
    
    // Выполняем математическое действие в зависимости от операции
    if (strcmp(op_str, "add") == 0) {
        result = a + b;
    } else if (strcmp(op_str, "subtract") == 0) {
        result = a - b;
    } else if (strcmp(op_str, "multiply") == 0) {
        result = a * b;
    } else if (strcmp(op_str, "divide") == 0) {
        if (b != 0) {
            result = a / b;
        } else {
            // Ошибка деление на ноль
            write(sock, "Error: Division by zero\n", strlen("Error: Division by zero\n"));
            close(sock);
            return;
        }
    } else {
        // Ошибка неверная операция
        write(sock, "Error: Invalid operation\n", strlen("Error: Invalid operation\n"));
        close(sock);
        return;
    }
    
    // Формируем сообщение с результатом
    char result_msg[50];
    sprintf(result_msg, "Result: %d\n", result);
    
    // Отправляем результат клиенту
    write(sock, result_msg, strlen(result_msg));
    
    printf("Client disconnected\n");
    close(sock);
}
