#include "unp.hpp"
#include "error.hpp"
#include "wrapsock.hpp"
#include "readline.hpp"


void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1, stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;

    FD_ZERO(&rset);
    for (; ;)
    {
        if (stdineof == 0)
        {
            FD_SET(fileno(fp), &rset);  
        }
        
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset))   /* socket is readable */
        {
            if ((n = read(sockfd, buf, MAXLINE)) == 0)
            {
               
               if (stdineof == 1)
               {
                   return;
               } else
               { 
                   err_quit("str_cli: server terminated prematurely");
               }
            }

            write(fileno(stdout), buf, n);
            
        }

        if (FD_ISSET(fileno(fp), &rset))  /* input is readable */
        {
            if ((n = read(fileno(fp), buf, MAXLINE)) == 0)
            {
                stdineof = 1;
                shutdown(sockfd, SHUT_WR); /* send FIN */
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            writen(sockfd, buf, n);
        }


    }

}
int main(int argc, const char ** argv) {

    int i, sockfd[1];

    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");
    
    for (int i = 0; i < 1; ++i)
    {
        sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
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
