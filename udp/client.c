#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define DEST_PORT 3000
#define DSET_IP_ADDRESS  "192.168.0.123"

int main()
{
    int sock_fd;/*套接字文件描述符*/
    int send_num;
    int recv_num;
    int dest_len;
    char send_buf[20]= {"hello tiger"};
    char recv_buf[20];
    struct sockaddr_in addr_serv;/*服务端地址，客户端地址*/

    sock_fd = socket(AF_INET,SOCK_DGRAM,0);//创建套接子
    //初始化服务器端地址
    memset(&addr_serv,0,sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
    addr_serv.sin_port = htons(DEST_PORT);

    dest_len = sizeof(struct sockaddr_in);
    printf("begin send:\n");
    send_num = sendto(sock_fd,send_buf,sizeof(send_buf),0,(struct sockaddr *)&addr_serv,dest_len);
    if(send_num < 0) {
        perror("sendto");
        exit(1);
    } else {

        printf("send sucessful:%s\n",send_buf);
    }
    recv_num = recvfrom(sock_fd,recv_buf,sizeof(recv_buf),0,(struct sockaddr *)&addr_serv,&dest_len);
    if(recv_num <0 ) {

        perror("recv_from");
        exit(1);
    } else {
        printf("recv sucessful\n");
    }
    recv_buf[recv_num]='\0';
    printf("the receive:%s\n",recv_buf);
    close(sock_fd);
    return 0;



}
