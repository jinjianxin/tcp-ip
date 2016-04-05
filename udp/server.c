#define SERV_PORT   3000


#if 0
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>


int main()
{
    int sock_fd;   //套接子描述符号
    int recv_num;
    int send_num;
    int client_len;
    char recv_buf[20];
    struct sockaddr_in  addr_serv;
    struct sockaddr_in  addr_client;//服务器和客户端地址
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);
    if(sock_fd < 0) {
        perror("socket");
        exit(1);
    } else {

        printf("sock sucessful\n");
    }
    //初始化服务器断地址
    memset(&addr_serv,0,sizeof(struct sockaddr_in));
    addr_serv.sin_family = AF_INET;//协议族
    addr_serv.sin_port = htons(SERV_PORT);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);//任意本地址

    client_len = sizeof(struct sockaddr_in);
    /*绑定套接子*/
    if(bind(sock_fd,(struct sockaddr *)&addr_serv,sizeof(struct sockaddr_in))<0 ) {
        perror("bind");
        exit(1);
    } else {

        printf("bind sucess\n");
    }
    while(1) {
        printf("begin recv:\n");
        recv_num = recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,(struct sockaddr *)&addr_client,&client_len);


        if(recv_num <  0) {
            printf("bad\n");
            perror("again recvfrom");
            exit(1);
        } else {
            recv_buf[recv_num]='\0';
            printf("recv sucess:%s\n",recv_buf);
        }
        printf("begin send:\n");
        send_num = sendto(sock_fd,recv_buf,recv_num,0,(struct sockaddr *)&addr_client,client_len);
        if(send_num < 0) {
            perror("sendto");
            exit(1);
        } else {
            printf("send sucessful\n");
        }
    }
    close(sock_fd);
    return 0;
}

#else

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int server_sockfd;
    int len;
    struct sockaddr_in my_addr;   //服务器网络地址结构体
    struct sockaddr_in remote_addr; //客户端网络地址结构体
    int sin_size;
    char buf[BUFSIZ];  //数据传送的缓冲区
    memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
    my_addr.sin_family=AF_INET; //设置为IP通信
    my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
    my_addr.sin_port=htons(SERV_PORT); //服务器端口号

    /*创建服务器端套接字--IPv4协议，面向无连接通信，UDP协议*/
    if((server_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)
    {
        perror("socket");
        return 1;
    }

    /*将套接字绑定到服务器的网络地址上*/
    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind");
        return 1;
    }
    sin_size=sizeof(struct sockaddr_in);
    printf("waiting for a packet...\n");

    /*接收客户端的数据并将其发送给客户端--recvfrom是无连接的*/

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


#endif