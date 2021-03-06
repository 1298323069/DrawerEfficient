#include "unp.h"
#include "error.c"
void sig_chld(int signo)
{
    pid_t   pid;
    int     stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}

void str_echo(int sockfd)
{
    ssize_t     n;
    char        buf[MAXLINE];
again:
    while ((n = read(sockfd, buf, MAXLINE)) > 0)
        write(sockfd, buf, n);
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");
}

int main(int argc, const char ** argv)
{
    int         listenfd, connfd;
    pid_t       childpid;
    socklen_t   clilen;
    struct sockaddr_un   cliaddr, servaddr;
    void   sig_chld(int);
    listenfd = socket(AF_LOCAL, SOCK_STREAM,0);
    unlink(UNIXSTR_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    bind(listenfd,(SA *)&servaddr, sizeof(servaddr));
    signal(SIGCHLD, sig_chld);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
            if (errno = EINTR)
                continue;        /* back to for() */
            else
                err_sys("accept error");
        }
        
        if ((childpid = fork()) == 0) {  /* child process */
            close(listenfd);      /* close listening socket */
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
    
    
}


































    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

