#include "head.h"

int main()
{
	int sockfd;
	char buff[BUFF_SIZE] = "hello";
	struct sockaddr_in clientaddr,
					   serveraddr;
	int ret;

	if( 0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("fail to open socket");
		return errno;
	}

	//fill client address
	memset(&clientaddr, 0, sizeof(SA));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(CLT_PORT);
	clientaddr.sin_addr.s_addr = inet_addr(CLT_ADDR);

	//fill server address
	memset(&serveraddr, 0, sizeof(SA));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SER_PORT);
	serveraddr.sin_addr.s_addr = inet_addr(SER_ADDR);


	if( 0 > connect(sockfd, (SA *)&serveraddr, sizeof(SA)))
	{
		perror("fail to connect");
		return errno;
	}

	while(1)
	{
		fgets(buff, BUFF_SIZE, stdin);
		if( !strcmp(buff, "quit\n"))
			break;
		if( 0 > (ret = send(sockfd, buff, strlen(buff) + 1, 0)))
		{
			perror("fail to send");
			return errno;
		}
		printf("send: %d\n", ret);

		ret = recv(sockfd, buff, BUFF_SIZE, 0);
		if(ret < 0)
		{
			perror("fail to receive");
			return errno;
		}
		printf("recv:[%d]:%s\n",ret, buff);

	}
	return 0;
}
