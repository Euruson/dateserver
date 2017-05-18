/****************************************************/
/************* datetime Example Server **************/
/****************************************************/
#include "datetime.h"
#include <time.h>

int main( int argc , char ** argv )
{
	time_t ticks;  
	char buff[ MAXLINE];

	int sock = -1; 
	if((sock = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	{
		printf("SOCKS ERROR!");
		return -1;
	} 

	const int opt = -1;

	//设置套接字类型  
	int nb = 0;
	nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));
	if(nb == -1)
	{
		printf("SET SOCKET ERROR!\n");
		return -1;
	}   
	struct sockaddr_in addrto;
	memset(&addrto, 0, sizeof(addrto));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = htonl(INADDR_BROADCAST);//套接字地址为广播地址
	addrto.sin_port = htons(2000);//套接字广播端口号为2000
	int nlen = sizeof(addrto);
	while(1)
	{
		ticks = time( NULL );
		snprintf(buff , sizeof( buff ) , "%.24s\r\n" , ctime( &ticks ));
		//向广播地址发布消息
		int ret=sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&addrto, nlen);
		if(ret < 0)
		{
			printf("SEND MASSAGE ERROR!\n");
			return -1;
		}
		else 
		{
			printf("BROADCAST SUCCEED!\n");
		}
		sleep(1);
	}
	return 0;
}
