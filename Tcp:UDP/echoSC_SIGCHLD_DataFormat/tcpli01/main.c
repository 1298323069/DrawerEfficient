#include "unp.h"
#include "sum.h"

void str_cli(FILE *fp, int sockfd)
{
    
    char sendline[MAXLINE];
    struct args         args;
    struct result       result;
    
    while (fgets(sendline,MAXLINE,fp) != NULL) {
        
        if (sscanf(sendline,"%ld%ld",&args.arg1,&args.arg2)!= 2) {
            printf("invalid input: %s",sendline);
            continue;
        }
        write(sockfd,&args,sizeof(args));
        
        if (read(sockfd,&result,sizeof(result)) == 0)
            printf("str_cli: server terminated prematurely");
        
        printf("%ld\n",result.sum);
        
            
    }

}
int main(int argc, const char ** argv) {
    
    int  i, sockfd[5];
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if (argc != 2)
        
        printf("usage: a.out <IPaddress>");
    
    
    for (i = 0; i < 5; i++) {
        
        if ((sockfd[i] =  socket(AF_INET, SOCK_STREAM, 0)) < 0)
            printf("socket error");
        
        bzero(&servaddr, sizeof(servaddr));
        
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
            printf("inet_pton error for %s",argv[1]);
        
        if (connect(sockfd[i],(SA *) &servaddr, sizeof(servaddr)) < 0)
            printf("connect error\n");
    }
    
    
    str_cli(stdin,sockfd[0]);
    
    exit(0);

}
