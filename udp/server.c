#define SERV_PORT   3000

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int server_sockfd;
    int len;
    struct sockaddr_in my_addr;   
    struct sockaddr_in remote_addr;
    int sin_size;
    char buf[BUFSIZ];  

    memset(&my_addr,0,sizeof(my_addr)); 
    my_addr.sin_addr.s_addr=INADDR_ANY;
    my_addr.sin_port=htons(SERV_PORT); 


    if((server_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        return 1;
    }

    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind");
        return 1;
    }
    sin_size=sizeof(struct sockaddr_in);
    printf("waiting for a packet...\n");

    char send_buf[20]= {"hello tiger"};

    static int count = 0;

    while(1)
    {

        if((len=recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&remote_addr,&sin_size))<0)
        {
            perror("recvfrom");
            return 1;
        }
        printf("received packet from %s:\n",inet_ntoa(remote_addr.sin_addr));
        buf[len]='\0';
        printf("contents: %s\n",buf);

        sendto(server_sockfd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&remote_addr, sin_size);

        count+=1;

        if(count>=5)
        {
            break;
        }

    }
    close(server_sockfd);
    return 0;
}

