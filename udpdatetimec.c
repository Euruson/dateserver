/****************************************************/
/************* datetime Example Client **************/
/****************************************************/

#include "datetime.h"

int main( int argc , char * * argv )
{
	char msg[MAXLINE+1]; 


	// 绑定地址 
	struct sockaddr_in addrto;
	memset(&addrto,0,sizeof(addrto)); 
	addrto.sin_family=AF_INET;
	addrto.sin_addr.s_addr=htonl(INADDR_ANY); 
	addrto.sin_port=htons(2000);
	socklen_t len=sizeof(addrto);

	int sock=-1;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("socket error...");
		return -1;
	}
	const int opt=-1;  

	//设置该套接字为广播类型 
	int nb=0;
	nb=setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(char*)&opt,sizeof(opt));
	if(nb==-1)
	{
		printf("set socket errror...");
		return -1;
	}
	if(bind(sock,(struct sockaddr*)&(addrto),len)==-1)
	{
		printf("bind error...");
		return -1;
	}

	//从广播地址接受消息 
	int ret=recvfrom(sock,msg,MAXLINE,0,(struct sockaddr*)&addrto,&len);
	if(ret<=0)
	{
		printf("read error\n");
	}
	else
	{
		printf("%s\n",msg);
	}
	return 0;
}
