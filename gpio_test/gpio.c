#include <stdio.h>
#include <stdint.h>     // for uint8_t
#include <unistd.h>
#include <fcntl.h>  	// for open

uint8_t gpio_pin = 60;

char *output = "out";
char *input = "in";

uint8_t high = 1;
uint8_t low = 0;

int main()
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

    int fd = 0;
    int bytes_written = 0;
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if( fd == -1)
	{
		printf("Open export failed\n");
	}

    bytes_written = write(fd, &gpio_pin, 1);
    if( bytes_written == -1)
	{
		printf("Write export failed\n");
	}

    close(fd);

    fd = open("/sys/class/gpio/gpio60/direction", O_WRONLY);
    if( fd == -1)
	{
		printf("Open direction failed\n");
	}

    bytes_written = write(fd, output, 3);
    if( bytes_written == -1)
	{
		printf("Write direction failed\n");
	}

    close(fd);

    fd = open("/sys/class/gpio/gpio60/value", O_WRONLY);
    if( fd == -1)
	{
		printf("Open direction failed\n");
	}

    while(1)
    {
        bytes_written = write(fd, &high, 1);
        if( bytes_written == -1)
        {
            printf("Write high value failed\n");
        }

        usleep(1000000);

        bytes_written = write(fd, &low, 1);
        if( bytes_written == -1)
        {
            printf("Write low value failed\n");
        }

        usleep(1000000);
    }

    close(fd);

}