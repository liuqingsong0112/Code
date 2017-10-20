/*
*TCP 服务端 客户端接口实现
*
*
*/

#ifndef TCP_H
#define TCP_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

/*public interface*/
extern int tcp_socket(void);

extern void TCP_CloseSocket(int sockfd);

/**
 * 计算 struct sockaddr 长度。 sizeof(struct sockaddr)
 *
 *
 * @return   addr_len
 */
int TCP_Addr_Len(void);

/**
 * 计算 struct sockaddr_in 长度。sizeof(struct sockaddr_in);
 *
 *
 * @return  sockaddr_in_len
 */
int TCP_Sockaddr_In_Len(void);

/**
 * 将地址加入到协议族中，填充ip和port
 *
 * @param server_addr 服务器地址
 * @return  成功返回 1
 */
extern int TCP_SetSockAddr(const char *ip, int port,struct sockaddr_in *server_addr);

/**
 * 设置服务端地址重用，绑定服务端地址
 * @param sockfd tcp套接字
 * @param server_addr 服务器地址
 * @return  成功返回 1
 */
extern int TCP_BindSockAddr(int sockfd,struct sockaddr_in *server_addr);

extern void TCP_CloseSocket(int sockfd);

/*TCP_server*/
/**
 * 初始化sockfd
 *
 *
 * @return    返回sockfd
 */
extern int TCP_serverInit(void);//return sockfd

/**
 * 接受客户端请求
 * @param sockfd tcp套接字
 *  @param client_addr 接受客户端地址
 * @return  接受客户端请求fd(accept_fd)
 */
extern int TCP_serverAccept(int sockfd,struct sockaddr_in *client_addr);

extern int TCP_serverClose(int sockfd,int accept_fd);

/*TCP_client*/
/**
 * 初始化sockfd
 *
 *
 * @return    返回sockfd
 */
extern int TCP_ClientInit();//return sockfd

/**
 * 接受客户端请求
 * @param sockfd tcp套接字
 * @param server_addr 连接服务器地址
 * @return  成功返回 1
 */
extern int TCP_ClientConnect(int sockfd,struct sockaddr_in* server_addr);

/**
 * 发送数据
 *
 * @param sockfd tcp套接字
 * @param pData  发送的数据 
 * @param maxlen    数据长度
 *
 * @return num   返回实际发送的字节数
 */
extern int TCP_Send(int sockfd, char *pData, int maxlen);

/**
 * 接受数据
 *
 * @param sockfd tcp套接字
 * @param pData  发送的数据 
 * @param maxlen    数据长度
 *
 * @return num   返回实际接受的字节数
 */
extern int TCP_Recv(int sockfd, char *pBuf, int maxlen);

#endif
