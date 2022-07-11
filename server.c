// Server side C program to demonstrate HTTP Server programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char hello[] =
        "HTTP/1.1 200 Ok\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html>\r\n"
        "<html><head><title>Sistemas Operacionais</title>\r\n"
        "<style>body{background-color: light-grey; text-align:center; background-color: lightgrey;font-family: 'Courier New';line-height: 30px;}</style>"
        "<body><h1>Hello World</h1><h2>Sistemas Operacionais 2022.1</h2><ul><li>Victor Emanuel Alves dos Santos</li><li>John Vasconcelos dos Santos</li><li>Teodoro Raulino Lima Neto</li><li>João Victor Leandro Nunes</li></ul></body>"
        "</html>";


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("\n------- ESPERANDO POR UMA NOVA CONEXAO -------\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello));
        printf("------------------Mensagem de Ola enviada!-------------------");
        close(new_socket);
    }
    return 0;
}