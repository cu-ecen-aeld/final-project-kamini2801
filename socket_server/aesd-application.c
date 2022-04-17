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

const char* UART = "/dev/hw_serial-481a8000";
int uart_fd = -1;
   
// Function designed for chat between client and server.
void func(int sockfd)
{
    char buff[MAX];
    //char val = 0;
    int n;
    for (;;) {
        printf("Open func");
        bzero(buff, sizeof(buff));
        printf("Enter the string on UART: \n");
        
        n = 0;
        int bytes_read = 0;
        do
        {
            bytes_read = read(uart_fd, &buff[n], 1);
            if(bytes_read <= 0) printf("Error read: %s", strerror(errno));
            printf("Value char:%c\n", buff[n]);
        }while (buff[n++] != '\r');

        printf("String:%s\n", buff);
        // write(sockfd, buff, sizeof(buff));
        // bzero(buff, sizeof(buff));
        // read(sockfd, buff, sizeof(buff));
        // printf("From Server : %s", buff);        
        // if ((strncmp(buff, "exit", 4)) == 0) {
        //     printf("Client Exit...\n");
        //     break;
        // }
    } 
}
   
// Driver function
int main()
{

    int sockfd = 0;
    // struct sockaddr_in servaddr;
   
    // // socket create and varification
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // if (sockfd == -1) {
    //     printf("socket creation failed...\n");
    //     exit(0);
    // }
    // else
    //     printf("Socket successfully created..\n");
    // bzero(&servaddr, sizeof(servaddr));
   
    // // assign IP, PORT
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = inet_addr("10.0.2.15");
    // servaddr.sin_port = htons(PORT);
   
    // // connect the client socket to server socket
    // if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
    //     printf("connection with the server failed...\n");
    //     exit(0);
    // }
    // else
    //     printf("connected to the server..\n");

    //Open uart device
    uart_fd = open(UART, O_RDWR);

    if(uart_fd < 0) {
        printf("Open UART failed with error : %d\n", uart_fd);
        //exit(-1);
    }
    // function for chat
    printf("Open UART succeeded");
    func(sockfd);
   
    // close the socket
    close(sockfd);
    

}