CC=$(CROSS_COMPILE)gcc


CFLAGS= -g -Wall -Werror


all: client server aesd-application
default: client server aesd-application

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

client : client.o
	$(CC) $(CFLAGS) client.o -o client

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

server : server.o
	$(CC) $(CFLAGS) server.o -o server

aesd-application.o: aesd-application.c
	$(CC) $(CFLAGS) -c aesd-application.c

aesd-application : aesd-application.o
	$(CC) $(CFLAGS) aesd-application.o -o aesd-application

clean :
	rm -f client server aesd-application *.o
