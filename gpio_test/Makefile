CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

all: gpio
default: gpio

gpio.o: gpio.c
	$(CC) $(CFLAGS) -c gpio.c

gpio : gpio.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) gpio.o -o gpio

clean :
	rm -f gpio *.o