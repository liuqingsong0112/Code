#include "tcp.h"

#define MAXDATA_LEN 1024

#define CLT_PORT	9999
#define CLT_ADDR	"172.16.63.67"

//./server

int main(int argc, const char *argv[])
{
	int nums;
	
	struct sockaddr_in server_addr;
	
	char pBuf[MAXDATA_LEN] = {0};
	
	int sockfd = 0;	
	
	//sockfd = TCP_serverInit(argv[1],(atoi(argv[2])));
	
	sockfd = TCP_ClientInit();

	TCP_SetSockAddr(CLT_ADDR, CLT_PORT, &server_addr);
	
	TCP_ClientConnect(sockfd, &server_addr);
		
	nums = TCP_Send(sockfd,"helloworld",MAXDATA_LEN);

	int ret;	

	ret = TCP_Recv(sockfd,pBuf,MAXDATA_LEN);
	
	printf("ret= %d pBuf=%s\n",ret, pBuf);
	
	TCP_CloseSocket(sockfd);
	
	return 0;
}

