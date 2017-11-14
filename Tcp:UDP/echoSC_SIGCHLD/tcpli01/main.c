#include "unp.h"


void str_cli(FILE *fp, int sockfd)
{
    char    sendline[MAXLINE],recvline[MAXLINE];
    
    while (fgets(sendline,MAXLINE,fp) != NULL) {
        write(sockfd,sendline,strlen(sendline));
        
        
        if (read(sockfd,recvline,MAXLINE) == 0)
            
            printf("str_cli: server terminated prematurely");
            
            
            
        fputs(recvline,stdout);
    }

}
int main(int argc, const char ** argv) {
    
    int sockfd;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if (argc != 2)
        
        printf("usage: a.out <IPaddress>");
    
    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0)
          printf("socket error");

    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        printf("inet_pton error for %s",argv[1]);

    if (connect(sockfd,(SA *) &servaddr, sizeof(servaddr)) < 0)
        printf("connect error\n");
    
    str_cli(stdin,sockfd);
    
    exit(0);

}
