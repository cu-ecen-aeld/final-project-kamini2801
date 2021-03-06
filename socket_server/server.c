/**
 * @file    :   server.c
 * @brief   :   This is the server code for AESD project. It reads data from the client and turns ON
 *              the respective LED.
 *              
 * @author  :   Sanish Kharade, Kamini Budke
 * @date    :   April 10
 * 
 * 
 * @link    :   For all functions - man pages and Linux System Programming book
 * 				Socket functions - https://beej.us/guide/bgnet/html/
 *              Reference - https://github.com/cu-ecen-aeld/Smart-Car-Dashboard/blob/main/sockettest/server.c 
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

#include <signal.h>     // for signals
#include <fcntl.h>  	// for open
#include <errno.h>		// for errno

#define MAX 80
#define PORT "8080"
#define PORT_INT 8080
#define SA struct sockaddr

#define PIN_66 "66"
#define PIN_67 "67"

#define PASSWORD "1234"

char *gpio_pin;

const char *output = "out";
const char *input = "in";
 
const char *high = "1";
const char *low = "0";

/**
 * @brief   :   Signal Handler function
 *              
 * @param   :   signo - Signal received
 *
 * @return  :   void
 * 
*/
static void signal_handler (int signo)
{
	// Keeping the signal handler as small as possible 

	if (signo == SIGINT)
	{
        printf("Caught SIGINT\n");
		//syslog(LOG_INFO, "Caught signal SIGINT, exiting\n");
	}
	else if (signo == SIGTERM)
	{
        printf("Caught SIGTERM\n"); 
		//syslog(LOG_INFO, "Caught signal SIGTERM, exiting\n");
	}
    int fd = 0;
    int bytes_written = 0;
    
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if( fd == -1)
	{
        printf("ERROR: open unexport() : %s \n", strerror(errno));
	}

    bytes_written = write(fd, PIN_67, 2);
    if( bytes_written == -1)
	{
        printf("ERROR: unexport 67() : %s \n", strerror(errno));
	}

    bytes_written = write(fd, PIN_66, 2);
    if( bytes_written == -1)
	{
        printf("ERROR: unexport 66() : %s \n", strerror(errno));
	}
    close(fd);
    exit(EXIT_SUCCESS);

}  
/**
 * @brief   :   Function to configure the GPIOs
 *              
 * @param   :   none
 * 
 * @return  :   void
 * 
*/
void configureGPIOs(void)
{
    int fd = 0;
    int bytes_written = 0;
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if( fd == -1)
	{
        printf("ERROR: open export() : %s \n", strerror(errno));
	}
    // green led
    gpio_pin = PIN_67;
    bytes_written = write(fd, PIN_67, 2);
    if( bytes_written == -1)
    {
        printf("ERROR: write export 67() : %s \n", strerror(errno));
    }

    // red led
    gpio_pin = PIN_66;
    bytes_written = write(fd, PIN_66, 2);
    if( bytes_written == -1)
    {
        printf("ERROR: write export 66() : %s \n", strerror(errno));
    }
    close(fd);   

    // set direction for the LEDs

    // green led
    fd = open("/sys/class/gpio/gpio67/direction", O_WRONLY);
    if( fd == -1)
    {
        printf("ERROR: open direction() : %s \n", strerror(errno));
    }
    bytes_written = write(fd, output, 3);
    if( bytes_written == -1)
    {
        printf("ERROR: write direction() : %s \n", strerror(errno));
    }
    close(fd);

    // red led
    fd = open("/sys/class/gpio/gpio66/direction", O_WRONLY);
    if( fd == -1)
    {
        printf("ERROR: open direction() : %s \n", strerror(errno));
    }

    bytes_written = write(fd, output, 3);
    if( bytes_written == -1)
    {
        printf("ERROR: write direction() : %s \n", strerror(errno));
    }

    close(fd);
}

/**
 * @brief   :   Function to turn ON Green LED
 *              
 * @param   :   none
 * 
 * @return  :   void
 * 
*/
void GreenLED_ON(void)
{
    int fd = 0;
    int bytes_written = 0;

    fd = open("/sys/class/gpio/gpio67/value", O_WRONLY);
    if( fd == -1)
    {
        printf("ERROR: open value() : %s \n", strerror(errno));
    }

    bytes_written = write(fd, high, 1);
    if( bytes_written == -1)
    {
        printf("ERROR: write high value() : %s \n", strerror(errno));
    }
    close(fd);
}

/**
 * @brief   :   Function to turn OFF Green LED
 *              
 * @param   :   none
 * 
 * @return  :   void
 * 
*/
void GreenLED_OFF(void)
{
    int fd = 0;
    int bytes_written = 0;
    fd = open("/sys/class/gpio/gpio67/value", O_WRONLY);
    if( fd == -1)
    {
        printf("ERROR: open value() : %s \n", strerror(errno));
    }

    bytes_written = write(fd, low, 1);
    if( bytes_written == -1)
    {
        printf("ERROR: write low value() : %s \n", strerror(errno));
    }

    close(fd);
}

/**
 * @brief   :   Function to turn ON Red LED
 *              
 * @param   :   none
 * 
 * @return  :   void
 * 
*/
void RedLED_ON(void)
{
    int fd = 0;
    int bytes_written = 0;
    fd = open("/sys/class/gpio/gpio66/value", O_WRONLY);
    if( fd == -1)
    {
        printf("ERROR: open value() : %s \n", strerror(errno));
    }

    bytes_written = write(fd, high, 1);
    if( bytes_written == -1)
    {
        printf("ERROR: write high value() : %s \n", strerror(errno));
    }
    close(fd);

}

/**
 * @brief   :   Function to turn OFF Red LED
 *              
 * @param   :   none
 * 
 * @return  :   void
 * 
*/
void RedLED_OFF(void)
{
    int fd = 0;
    int bytes_written = 0;
    fd = open("/sys/class/gpio/gpio66/value", O_WRONLY);
    if( fd == -1)
    {
        printf("ERROR: open value() : %s \n", strerror(errno));
    }

    bytes_written = write(fd, low, 1);
    if( bytes_written == -1)
    {
        printf("ERROR: write low value() : %s \n", strerror(errno));
    }

    close(fd);
}
/**
 * @brief   :   Function to communicate with client
 *              
 * @param   :   sockfd - socket file descriptor
 * 
 * @return  :   void
 * 
*/
void func(int sockfd)
{
    char buff[MAX];
    char *str;

    // infinite loop for communication
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("Client input = %s\n", buff);

        if(strncmp(buff, PASSWORD, 4) == 0)
        {
            GreenLED_ON();
            RedLED_OFF();
            str = "Access Granted\n";
        }
        else
        {
            GreenLED_OFF();
            RedLED_ON();
            str = "Access Denied\n";
        }

        write(sockfd, str, strlen(str));
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
   
/**
 * @brief   :   Main entry point into the application
 *              
 * @param   :   none
 * 
 * @return  :   void
 * 
*/
int main(void)
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   

   	/*
	* Register signal_handler as our signal handler
	* for SIGINT and SIGTERM.
	*/
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
        printf("ERROR: Could not register SIGINT handler\n");
		exit (EXIT_FAILURE);
	}

	if (signal(SIGTERM, signal_handler) == SIG_ERR)
	{
        printf("ERROR: Could not register SIGTERM handler\n");
		exit (EXIT_FAILURE);
	}

    configureGPIOs();
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT_INT);
   

	/* getaddrinfo() returns a list of address structures.
	  Try each address until we successfully bind.
	  If socket (or bind) fails, we (close the socket
	  and) try the next address.
	  Ref -  man page of getaddrinfo
	 */
	//syslog(LOG_DEBUG, "Attempting to Bind\n");
	int status;
    struct addrinfo hints;
	struct addrinfo *result, *rp;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, PORT, &hints, &result);
	if(status != 0)
	{
		//syslog(LOG_ERR, "ERROR: getaddrinfo() : %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd == -1)
		{
			/* socket() failed */
			exit(EXIT_FAILURE);
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    	{
        	exit(EXIT_FAILURE);
    	}
		bzero(&servaddr, sizeof(servaddr));
		if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
		{
			/* Successfully bound to socket */
			break;                  
		}
	
		close(sockfd);
	}
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, (unsigned int *)&len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accepted the client...\n");
   
    // Function for chatting between client and server
    func(connfd);
   
    // After chatting close the socket
    close(sockfd);
}