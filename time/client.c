#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXBUFFER 512
#define PORT 6666 
#define HOST_ADDR

int main(int argc,char *argv)
{
	int sockfd,n;
	char recvbuffer[MAXBUFFER];
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd<0)
	{
		printf("socket create failed\n");
		return -1;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("connection....\n");

	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
	{
		printf("connection failed\n");
		return -1;
	}

	while((n = read(sockfd,recvbuffer,MAXBUFFER))>0)
	{
		recvbuffer[n] = 0;
		fputs(recvbuffer,stdout);
	}

	if(n<0)
	{
		printf("read failed\n");
		return -2;
	}

	return 0;
}
