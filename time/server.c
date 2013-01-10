#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define LISTEN 5
#define MAXLINE 512

int main(int argc,char *argv[])
{
	int listenfd,connfd;

	socklen_t len;
	struct sockaddr_in seraddr,cliaddr;
	char buf[MAXLINE];

	time_t ticks;

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	if(listenfd<0)
	{
		printf("Socket createt failed;\n");
		return -1;
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(6666);
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0)
	{
		printf("bind failed\n");
		return -1;
	}
	
	printf("listening......\n");

	listen(listenfd,LISTEN);

	while(1)
	{
		len = sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);
		printf("connect from %s,port %d\n",inet_ntoa(cliaddr.sin_addr.s_addr),ntohs(cliaddr.sin_port));
		
		ticks = time(NULL);
		sprintf(buf,"%.24s \r \n",ctime(&ticks));
		write(connfd,buf,strlen(buf));
		close(connfd);

	}
}
