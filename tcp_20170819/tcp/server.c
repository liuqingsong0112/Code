#include "tcp.h"

#define NUM 1024
#define SER_PORT	9999
#define SER_ADDR	"172.16.63.67"

//./server
int main(int argc, const char *argv[])
{	
	int sockfd = 0;
	int num = 0;
	int SockOptVal_ReuseAddr = 1;
	char pBuf[1024];
	
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
		
	sockfd = TCP_serverInit();

	TCP_SetSockAddr(SER_ADDR, SER_PORT, &server_addr);
	
	TCP_BindSockAddr(sockfd, &server_addr);
	
	listen(sockfd,50);

	int accept_fd = TCP_serverAccept(sockfd, &client_addr);
	
	num = TCP_Recv(accept_fd,pBuf,NUM);

	printf("num =%d pBuf=%s\n", num, pBuf);

	TCP_Send(accept_fd,"server",NUM);
		
	TCP_serverClose(sockfd, accept_fd);
	
	return 0;
}

