#include "unp.h"
void str_echo(int sockfd)
{
    ssize_t    n;
    char       buf[MAXLINE];
    
again:
    while ((n = read(sockfd,buf,MAXLINE)) > 0) {
        
        write(sockfd,buf,n);
        
        if (n < 0 && errno == EINTR) {
            goto again;
            
        } else if (n < 0){
            //            err_sys("str_echo: read error");
        }
        
    }
    
}

void sig_chld(int signo)
{
    pid_t pid;
    int   stat;
    
    while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
    {
        printf("child %d terminated\n",pid);
        
    }
    
    return;
    
}


int main(int argc, const char ** argv) {
    
    int            listenfd, connfd, udpfd, nready, maxfdp1;
    char           mesg[MAXLINE];
    pid_t          childpid;
    fd_set         rset;
    ssize_t        n;
    socklen_t      len;
    const   int    on = 1;
    struct  sockaddr_in cliaddr, servaddr;
    void sig_child(int);
    
    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    setsockopt(listenfd, SQL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr);
    listen(listenfd, LISTENQ);
         
    /* create UDP socket */
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    bind(udpfd, (SA *) &servaddr, sizeof(servaddr));
    signal(SIGCHLD, sig_child); /* must call waitpid() */
    
    FD_ZERO(&rset);
    maxfdp1 = max(listenfd, udpfd) + 1;
    for (; ; ) {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);
        if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
            if (errno = EINTR)
                continue;
            else
                err_sys("select error");
        }
        
        if (FD_ISSET(listenfd, &rset)) {
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (SA *) &cliaddr, &len);
            
            if ((childpid = fork()) == 0) { /*child progress*/
                close(listenfd);
                str_echo(connfd);
                exit(0);
            }
            close(connfd); /* parent closes connected sockets */
        }
        
        if (FD_ISSET(udpfd, &rset)) {
            len = sizeof(cliaddr);
            n = recvfrom(udpfd, mesg, MAXLINE, 0, &cliaddr, &len);
            sendto(udpfd, mesg, n, 0, (SA *) &cliaddr, len);
            

        }
    }
    
    
}





























