/*
*   
*   File:       aesd-application.c
*   Brief:      Application to run and accept input pn custom UART on the client side
*   Author:     Kamini Budke Sanish Kharade
*   Date:       04-14-2022
*   Reference:  https://github.com/cu-ecen-aeld/assignments-3-and-later-kamini2801/blob/master/server/aesdsocket.c
*
*/

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define IP_PATH "ip"

const char* UART = "/dev/hw_serial-481a8000";
const char* init_print = "Please enter password to login into System\n";
const char* password = "Enter password:\n";

int uart_fd = -1;
   
char ip[16];

/**
 * @brief   :   task for accepting input from UART and communicating with server
 *              
 * @param   :   socket file descriptor
 *
 * @return  :   void
 * 
*/
void func(int sockfd)
{
    char buff[MAX];
    //char val = 0;
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
                
        n = 0;
        int bytes_read, bytes_write = 0;
        int str_size = 0;

        bytes_write = write(uart_fd, password, strlen(password));
        if( bytes_write == -1)
        {
            printf("ERROR: uart write() :%s\n", strerror(errno)); 
        }
        do
        {
            bytes_read = read(uart_fd, &buff[n], 1);
            if( bytes_read == -1)
            {
                printf("ERROR: uart read() :%s\n", strerror(errno)); 
            }

            bytes_write = write(uart_fd, &buff[n], 1);
            if( bytes_write == -1)
            {
                printf("ERROR: uart write() :%s\n", strerror(errno)); 
            }
            str_size++;

        }while (buff[n++] != '\r');

        printf("String:%s\n", buff);

        //send to socket
        int ret_wrt = write(sockfd, buff, sizeof(buff));
        if(ret_wrt < 0) {
            printf("write socket error: %s", strerror(errno));
        }
        printf("Write success with %d bytes\n", ret_wrt);
        
        //read from socket
        bzero(buff, sizeof(buff));
        int sock_len = read(sockfd, buff, sizeof(buff));
        if( sock_len < 0){
            printf("read socket error: %s", strerror(errno));
        }

        printf("From Server : %s", buff);  
        write(uart_fd, buff, sock_len);      

    } 
}
   

int main()
{

    int sockfd = 0;
    int n_read = 0;
    int byte_write = 0;
    struct sockaddr_in servaddr;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    //get ip from configuration text file
    int ip_fd = open(IP_PATH,O_RDONLY);
    if(ip_fd == -1)
    {
        printf("ERROR: open() :%s\n", strerror(errno));
    }

    while((n_read = read(ip_fd, ip, sizeof(ip) ))!=0)
    {
        if(n_read == -1)
        {
            printf("ERROR: read() :%s\n", strerror(errno));
        }
    }
    close(ip_fd);

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server\n");

    //Open uart device
    uart_fd = open(UART, O_RDWR);

    if(uart_fd < 0) {
        printf("Open UART failed with error : %s\n", strerror(errno));
        //exit(-1);
    }

    byte_write = write(uart_fd, init_print, strlen(init_print));
    if(byte_write < 0){
        printf("UART init write failed with error : %s\n", strerror(errno));
    }

    // function for chat
    printf("Open UART succeeded, enter in UART terminal\n");
    func(sockfd);
   
    // close the socket
    close(sockfd);
    

}   