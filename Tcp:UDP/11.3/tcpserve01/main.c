#include "unp.h"
#include "error.c"
#include <time.h>

#define MAXFD   64

extern int daemon_proc;

int daemon_init(const char *pname, int facility)
{
    int i;
    pid_t pid;
    
    if ((pid = fork()) < 0)
        return(-1);
    else if(pid)
        _exit(0);        /* parent terminates */
    
    /* child 1 continues */
    
    if (setsid() < 0)  /* become session leader */
        return(-1);
    
    signal(SIGHUP, SIG_IGN);
    if ((pid = fork()) < 0)
        return(-1);
    else if(pid)
        _exit(0);             /* child 1 terminates */
    
    /* child 2 continues ... */
    
    daemon_proc = 1;          /* for err_XXX() functions */
    
    chdir("/");               /* change working directory */
    
    /* close off file descriptors */
    for ( i = 0; i < MAXFD; i++)
        close(i);
    
    /* rediect stdin, stdout, stderr to /dev/null */
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    
    openlog(pname, LOG_PID, facility);
    
    return(0);   /*success*/
    
}
char *sock_ntop(const struct sockaddr *sa, socklen_t len)
{
    char    portstr[8];
    static char str[128];
    switch (sa->sa_family) {
        case AF_INET:{
            struct sockaddr_in  *sin = (struct sockaddr_in *)sa;
            if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                return(NULL);
            if (ntohs(sin->sin_port) != 0) {
                snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
                strcat(str, portstr);
            }
            return str;
        }
    }
    
}

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
    int     listenfd, n;
    const   int on = 1;
    struct  addrinfo hints, *res, *ressave;
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        printf("tcp_listen error for %s, %s: %s", host, serv, gai_strerror(n));
    ressave = res;
    do{
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;              /* error, try next one */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;                 /* success */
        close(listenfd);
    } while ((res = res->ai_next) != NULL);
    
    if (res == NULL)             /* errno from final socket() or bind() */
        printf("tcp_listen error for %s, %s", host, serv);
    
    listen(listenfd, LISTENQ);
    
    if (addrlenp)
        *addrlenp = res->ai_addrlen;  /* return size of protocol address */
    freeaddrinfo(ressave);
    
    return(listenfd);
}
int main(int argc, const char ** argv) {

    int listenfd, connfd;
    socklen_t addrlen, len;
    struct  sockaddr *cliaddr;
    char    buff[MAXLINE];
    time_t  ticks;
    
    if (argc < 2 || argc > 3)
        err_quit("usage: daytimetcpsrv2 [ <host> ] <service or port>");
    
    daemon_init(argv[0], 0);
    
    if (argc == 2)
        listenfd = tcp_listen(NULL, argv[1], &addrlen);
    else
        listenfd = tcp_listen(argv[1], argv[2], &addrlen);
    
    cliaddr =  malloc(addrlen);
    
    for (; ; ) {
        len = addrlen;
        connfd = accept(listenfd, cliaddr, &len);
        err_msg("connection from %s", sock_ntop(cliaddr, len));
        
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s/r/n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
   
    
}






















