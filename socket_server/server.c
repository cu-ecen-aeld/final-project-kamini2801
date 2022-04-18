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
#define PORT 8080
#define SA struct sockaddr

char *gpio_pin;

char *output = "out";
char *input = "in";

char *high = "1";
char *low = "0";

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

    bytes_written = write(fd, "67", 2);
    if( bytes_written == -1)
	{
        printf("ERROR: unexport 67() : %s \n", strerror(errno));
	}

    bytes_written = write(fd, "66", 2);
    if( bytes_written == -1)
	{
        printf("ERROR: unexport 66() : %s \n", strerror(errno));
	}
    close(fd);
    exit(EXIT_SUCCESS);

}  

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
    gpio_pin = "67";
    bytes_written = write(fd, "67", 2);
    if( bytes_written == -1)
    {
        printf("ERROR: write export 67() : %s \n", strerror(errno));
    }

    // red led
    gpio_pin = "66";
    bytes_written = write(fd, "66", 2);
    if( bytes_written == -1)
    {
        printf("ERROR: write export 66() : %s \n", strerror(errno));
    }
    close(fd);   

    // set direction for the LEDs

    // gren led
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
// Function designed for chat between client and server.
void func(int sockfd)
{
    char buff[MAX];
    char *str;
    //int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("Client input = %s\n", buff);

        if(strncmp(buff, "1234", 4) == 0)
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

        
        // bzero(buff, MAX);
        // n = 0;
        // // copy server message in the buffer
        // while ((buff[n++] = getchar()) != '\n')
        //     ;
   
        // and send that buffer to client
        //write(sockfd, buff, sizeof(buff));
        write(sockfd, str, strlen(str));
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
   
// Driver function
int main()
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
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
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