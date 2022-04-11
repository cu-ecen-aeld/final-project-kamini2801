#include <stdio.h>
#include <stdint.h>     // for uint8_t
#include <unistd.h>
#include <fcntl.h>  	// for open
#include <errno.h>		// for errno
#include <string.h>     // for strerror

#include <stdlib.h>     // for system
#include <signal.h>     // for signals

// char *gpio_pin = "60";
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
		//printf("Open export failed\n");
	}

    bytes_written = write(fd, gpio_pin, 2);
    if( bytes_written == -1)
	{
        printf("ERROR: write export() : %s \n", strerror(errno));
		//printf("Write export failed\n");
	}
    close(fd);
    exit(EXIT_SUCCESS);

}
int main(int argc, char *argv[])
{
    // FILE *io,*iodir,*ioval;

    // io = fopen("/sys/class/gpio/export", "w");
    // fseek(io,0,SEEK_SET);
    // fprintf(io,"%d",39);
    // fflush(io);

    // iodir = fopen("/sys/class/gpio/gpio60/direction", "w");
    // fseek(iodir,0,SEEK_SET);
    // fprintf(iodir,"out");
    // fflush(iodir);

    // ioval = fopen("/sys/class/gpio/gpio60/value", "w");
    // fseek(ioval,0,SEEK_SET);

    // while(1)
    // {
    //     fprintf(ioval,"%d",1);
    //     fflush(ioval);
    //     sleep(1);
    //     fprintf(ioval,"%d",0);
    //     fflush(ioval);
    //     sleep(1);
    // }

    // fclose(io);
    // fclose(iodir);
    // fclose(ioval);
    // return 0;
	/*
	* Register signal_handler as our signal handler
	* for SIGINT and SIGTERM.
	*/
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
        printf("ERROR: Could not register SIGINT handler\n");
		//syslog(LOG_ERR, "ERROR: Could not register SIGINT handler\n");
		exit (EXIT_FAILURE);
	}

	if (signal(SIGTERM, signal_handler) == SIG_ERR)
	{
        printf("ERROR: Could not register SIGTERM handler\n");
		//syslog(LOG_ERR, "ERROR: Could not register SIGTERM handler\n");
		exit (EXIT_FAILURE);
	}

    int fd = 0;
    int bytes_written = 0;
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if( fd == -1)
	{
        printf("ERROR: open export() : %s \n", strerror(errno));
		//printf("Open export failed\n");
	}
    if(strcmp(argv[1], "1234") == 0)
    {
        // green led
        gpio_pin = "67";
        bytes_written = write(fd, "67", 2);
        if( bytes_written == -1)
        {
            printf("ERROR: write export 67() : %s \n", strerror(errno));
            //printf("Write export failed\n");
        }
        close(fd);
        fd = open("/sys/class/gpio/gpio67/direction", O_WRONLY);
        if( fd == -1)
        {
            printf("ERROR: open direction() : %s \n", strerror(errno));
            //printf("Open direction failed\n");
        }
        bytes_written = write(fd, output, 3);
        if( bytes_written == -1)
        {
            printf("ERROR: write direction() : %s \n", strerror(errno));
            //printf("Write direction failed\n");
        }

        close(fd);

        fd = open("/sys/class/gpio/gpio67/value", O_WRONLY);
        if( fd == -1)
        {
            printf("ERROR: open value() : %s \n", strerror(errno));
            //printf("Open direction failed\n");
        }
    }
    else
    {
        // red led
        gpio_pin = "66";
        bytes_written = write(fd, "66", 2);
        if( bytes_written == -1)
        {
            printf("ERROR: write export 66() : %s \n", strerror(errno));
            //printf("Write export failed\n");
        }
        close(fd);
        fd = open("/sys/class/gpio/gpio66/direction", O_WRONLY);
        if( fd == -1)
        {
            printf("ERROR: open direction() : %s \n", strerror(errno));
            //printf("Open direction failed\n");
        }

        //close(fd);
        bytes_written = write(fd, output, 3);
        if( bytes_written == -1)
        {
            printf("ERROR: write direction() : %s \n", strerror(errno));
            //printf("Write direction failed\n");
        }

        close(fd);

        fd = open("/sys/class/gpio/gpio66/value", O_WRONLY);
        if( fd == -1)
        {
            printf("ERROR: open value() : %s \n", strerror(errno));
            //printf("Open direction failed\n");
        }
    }
    // bytes_written = write(fd, gpio_pin, 2);
    // if( bytes_written == -1)
	// {
    //     printf("ERROR: write export() : %s \n", strerror(errno));
	// 	//printf("Write export failed\n");
	// }

    //close(fd);

    //system("echo 60 > /sys/class/gpio/export");

    // fd = open("/sys/class/gpio/gpio60/direction", O_WRONLY);
    // if( fd == -1)
	// {
    //     printf("ERROR: open direction() : %s \n", strerror(errno));
	// 	//printf("Open direction failed\n");
	// }

    // bytes_written = write(fd, output, 3);
    // if( bytes_written == -1)
	// {
    //     printf("ERROR: write direction() : %s \n", strerror(errno));
	// 	//printf("Write direction failed\n");
	// }

    // close(fd);

    // fd = open("/sys/class/gpio/gpio60/value", O_WRONLY);
    // if( fd == -1)
	// {
    //     printf("ERROR: open value() : %s \n", strerror(errno));
	// 	//printf("Open direction failed\n");
	// }

    while(1)
    {
        bytes_written = write(fd, high, 1);
        if( bytes_written == -1)
        {
            printf("ERROR: write high value() : %s \n", strerror(errno));
            //printf("Write high value failed\n");
        }

        usleep(1000000);

        bytes_written = write(fd, low, 1);
        if( bytes_written == -1)
        {
            printf("ERROR: write low value() : %s \n", strerror(errno));
            //printf("Write low value failed\n");
        }

        usleep(1000000);
    }

    close(fd);

}