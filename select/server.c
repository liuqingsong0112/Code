#include "head.h"

int main()
{
	int sockfd, connfd;
	struct sockaddr_in serveraddr,
					   peeraddr;
	int addrlen = sizeof(SA);

	int maxfd;
	fd_set rdfs, tmp_rdfs;
	int i;

	char buff[BUFF_SIZE];

	if(0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_handler("socket");

	memset(&serveraddr, 0, sizeof(SA));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	serveraddr.sin_port = htons(SER_PORT);

	if( 0 > bind(sockfd, (SA *)&serveraddr, sizeof(SA)))
		error_handler("bind");

	if( 0 > listen(sockfd, 5))
		error_handler("listen");

	FD_ZERO(&rdfs);
	FD_SET(sockfd, &rdfs);
	maxfd = sockfd;

	while(1)
	{
		tmp_rdfs = rdfs;
		if( 0 > select(maxfd+1, &tmp_rdfs, NULL, NULL, NULL))
			error_handler("select");
		
		for(i = 3; i <= maxfd; i ++)
		{
			if(FD_ISSET(i, &tmp_rdfs))
			{
				if(i == sockfd)
				{
					if( 0 > (connfd = accept(sockfd, (SA *)&peeraddr, &addrlen)))
						error_handler("accept");
					printf("accept->%s:%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
					FD_SET(connfd, &rdfs);
					maxfd = connfd > maxfd ? connfd : maxfd;
				}
				else
				{
					if( 0 < recv(i, buff, BUFF_SIZE, 0))
					{
						puts(buff);
						if( 0 > send(i, buff, strlen(buff)+1, 0))
							perror("send");
					}
					else
					{
						printf("quit->%s:%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
						close(i);
						FD_CLR(i, &rdfs);
					}
				}
			}
		}
	}

}
