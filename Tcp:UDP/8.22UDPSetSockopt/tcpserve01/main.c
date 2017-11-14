#include "unp.h"
static int count;


static void recvfrom_int(int signo)
{
    printf("\nreceived %d datagrams\n",count);
    exit(0);
}

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
    int       n;
    socklen_t len;
    char      mesg[MAXLINE];
    signal(SIGINT, recvfrom_int);
    
    n = 220 * 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n));
    
    for (; ; ) {
        len = clilen;
        recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        count++;
        
    }

}

int main(int argc, const char ** argv) {

    
    int                   sockfd;
    struct sockaddr_in    servaddr, cliaddr;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));
    
    dg_echo(sockfd, (SA*) &cliaddr, sizeof(cliaddr));
    
}
