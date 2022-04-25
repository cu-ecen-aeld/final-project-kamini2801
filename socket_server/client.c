/*
<<<<<<< Updated upstream
*   
*   File:       client.c
*   Brief:      Test code to run cleint on BBB
*   Author:     Kamini Budke Sanish Kharade
*   Date:       04-10-2022
*   Reference:  https://github.com/cu-ecen-aeld/Smart-Car-Dashboard/blob/main/sockettest/client.c
=======
*   Reference: https://github.com/cu-ecen-aeld/Smart-Car-Dashboard/blob/main/sockettest/client.c
>>>>>>> Stashed changes
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

char ip[16];

/**
 * @brief   :   task for communicating with server
 *              
 * @param   :   socket file descriptor
 *
 * @return  :   void
 * 
*/

void comm_task(int sockfd)
{
    char buff[MAX];
    int n, r_bytes, w_bytes;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;

        //parse till newline encountered
        while ((buff[n++] = getchar()) != '\n')
            ;

        //send data onto socket
        w_bytes = write(sockfd, buff, sizeof(buff));
        if(w_bytes == -1)
        {
           printf("ERROR: sokcet write() :%s\n", strerror(errno)); 
        }

        //reset buffer
        bzero(buff, sizeof(buff));

        //read from socket
        r_bytes = read(sockfd, buff, sizeof(buff));
        if(r_bytes == -1)
        {
           printf("ERROR: socket read() :%s\n", strerror(errno)); 
        }

        printf("From Server : %s", buff);

        //exit functionality
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}
   
int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    int n_read = 0;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");


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

    printf("Retrieved ip: %s\n", ip);

    // assign IP, PORT
    bzero(&servaddr, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
   
    // function for communication
    comm_task(sockfd);
   
    // close the socket
    close(sockfd);
}
