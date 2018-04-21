#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#define error_handler(Mesg)	\
	do{perror(Mesg);exit(EXIT_FAILURE);}while(0);

#define SER_PORT	10001
#define SER_ADDR	"192.168.1.10"
#define CLT_PORT	20002
#define CLT_ADDR	"192.168.1.200"

#define BUFF_SIZE	128

typedef struct sockaddr SA;

