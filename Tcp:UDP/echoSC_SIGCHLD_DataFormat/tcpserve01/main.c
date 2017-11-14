#include "unp.h"
#include "sum.h"

void str_echo(int sockfd)
{
    
    ssize_t  n;
    struct args        args;
    struct result      result;
    for (; ; ) {
        
        if ((n = read(sockfd, &args, sizeof(args))) == 0)
            return;/*connection close by other*/
        
        result.sum = args.arg1 + args.arg2;
        
        write(sockfd,&result,sizeof(result));
        
            
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

Sigfunc *signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;
    
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        
        act.sa_flags |= SA_INTERRUPT;
        
#endif
    } else
    {
#ifdef  SA_RESTART
        
        act.sa_flags |= SA_RESTART;
        
#endif
    }
    
    if (sigaction(signo,&act,&oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
    
}
int main(int argc, const char ** argv) {

    int      listenfd,connfd;
    pid_t    childpid;
    socklen_t clilen;
    
    struct sockaddr_in cliaddr, servaddr;
    
    void sig_chld(int);
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    servaddr.sin_port = htons(SERV_PORT);
    
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
    listen(listenfd, LISTENQ);
    
    signal(SIGCHLD,sig_chld);
    
    for (; ; ) {
        
        clilen = sizeof(cliaddr);
        
         if ((connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0) {
            
            if (errno == EINTR) {
                
                continue;
                
            } else
            {
                printf("accept error");
            }
            
            
        } 
        
        
        if ((childpid = fork()) == 0) {/*child process*/
            close(listenfd);           /* close listening socket*/
            str_echo(connfd);          /*process the request*/
            exit(0);
            
        }
        close(connfd);/*parent closes connected socket*/
        
    }
   
    return 0;
}
