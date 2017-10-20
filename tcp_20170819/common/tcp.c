#include "tcp.h"

int tcp_socket(void)
{
	int  sockfd = 0;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("Fail to socket ");
		exit(EXIT_FAILURE);
	}	
	
	return sockfd;
}

void TCP_CloseSocket(int sockfd)
{
	close(sockfd);
}

int TCP_Addr_Len(void)
{
	int addr_len = sizeof(struct sockaddr);
	
	return addr_len;
}

int TCP_Sockaddr_In_Len(void)
{
	int sockaddr_in_len = sizeof(struct sockaddr_in);
	
	return sockaddr_in_len;
}

int TCP_SetSockAddr(const char *ip, int port,struct sockaddr_in *server_addr)
{
	if(server_addr == NULL) return 0;
	
	bzero(server_addr, sizeof(struct sockaddr_in));
	server_addr->sin_family = AF_INET;
	server_addr->sin_port   = htons(port);
	server_addr->sin_addr.s_addr = inet_addr(ip);
	
	return 1;
}

int TCP_BindSockAddr(int sockfd,struct sockaddr_in *server_addr)
{
	if(server_addr == NULL) return 0;

	int sockoptval = 1;	

	int addr_len = TCP_Addr_Len();

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(sockoptval)) == -1)
	{
		printf("setsockopt failed\n");
		close(sockfd);
		return 0;
	}
	
	if(bind(sockfd, (struct sockaddr *)server_addr, addr_len) < 0)
	{
		perror("Fail to bind");
		return 0;
	}
	
	return 1;
}

int TCP_Select(int sockfd)
{
	int ret = 0;
	int fd_isset_value = 0;
	fd_set read_fds;
	struct timeval timeout;//select等待10秒，10秒轮询，要非阻塞返回0  
	
	FD_ZERO(&read_fds);
	FD_SET(sockfd, &read_fds);
	
	timeout.tv_sec = 10;  
	timeout.tv_usec = 0;

	ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout) ; //select使用  
	  
	if(ret < 0)
	{	 
		printf("ret == -1\n");
		return 0;  
	}
	else if(ret == 0)
	{ 
		printf(" 10s out,time out, return 0\n");
		return 0;
	}
	else
	{
		fd_isset_value = FD_ISSET(sockfd, &read_fds) ; //测试sock是否可读，即是否网络上有数据  
		
		printf("fd_isset_value=%d\n",fd_isset_value);
	}

	return fd_isset_value;
}

/*********************************************************
*
*  TCP_Server
*
*
**********************************************************/

int TCP_serverInit(void)//return sockfd
{
	int  sockfd = tcp_socket();
	
	return sockfd;
}

int TCP_serverAccept(int sockfd,struct sockaddr_in* client_addr)
{
	int accept_fd = 0;	

	int addr_len = sizeof(struct sockaddr);

	int select_value = TCP_Select(sockfd);	

	if(select_value == 1)
	{
	//提起请求
	accept_fd = accept(sockfd,(struct sockaddr *)client_addr,&addr_len);
	if(accept_fd < 0)
	{
		perror("Fail to accept");
		exit(EXIT_FAILURE);
	}
	
	printf("***********************\n");
	printf("Ip : %s.\n",inet_ntoa(client_addr->sin_addr));
	printf("Port: %d.\n",ntohs(client_addr->sin_port));
	printf("***********************\n");
	}
	return accept_fd;
}

int TCP_serverClose(int sockfd, int accept_fd)
{
	close(sockfd);

	close(accept_fd);
}

/*********************************************************
*
*  TCP_Client
*
*
**********************************************************/
int TCP_ClientInit(const char *ip, int port)//return sockfd
{
	int sockfd = tcp_socket();
#if 0
	struct sockaddr_in server_addr;
	
	bzero(&server_addr,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	//建立连接
	if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) < 0)
	{
		perror("Fail to bind");
		exit(EXIT_FAILURE);
	}
	
#endif

	return sockfd;
}

int TCP_ClientConnect(int sockfd,struct sockaddr_in* server_addr)
{
	if(connect(sockfd,(struct sockaddr *)server_addr,sizeof(struct sockaddr)) < 0)
	{
		perror("Fail to bind");
		return 0;
	}
	
	return 1;
}

int TCP_Send(int sockfd, char *pData, int maxlen)
{
	int num  = send(sockfd,pData,maxlen,0);
	
	return num;
}

int TCP_Recv(int sockfd, char *pBuf, int maxlen)
{
	int num = 0;
		num = recv(sockfd,pBuf,maxlen,0);
		pBuf[num] = '\0';

		printf("Read %d bytes : %s.\n",num,pBuf);
	

	return num;
}




#if 0
int TCP_clientSend(int sockfd, char *pData, int len)
{
	//发
	int num = send(sockfd,pData,len,0);
	
	return num;
}

int TCP_clientRecv(int sockfd, char *pBuf,int maxlen)
{
	//收数据
	memset(pBuf,0,maxlen);
	int num = recv(sockfd,pBuf,maxlen,0);
	printf("pBuf=%s num=%d\n",pBuf,num);
	return num;
}

#endif
