#include "unp.hpp"
#include "signal.hpp"
#include "sigchldwait.hpp"
#include "error.hpp"
#include "readline.hpp"
#include <limits.h>   /* for OPEN_MAX */
#include "checkopts.hpp"

void str_echo(int sockfd)
{

    long arg1, arg2;

    ssize_t    n;
    char       buf[MAXLINE];
    
again:
    while ((n = readline(sockfd,buf,MAXLINE)) > 0) {
        
        write(sockfd,buf,n);
        
        if (n < 0 && errno == EINTR) {
            goto again;
            
        } else if (n < 0){
           err_sys("str_echo: read error");
        }
        
    }

}

int main(int argc, const char ** argv) {
    /*
    * *************************get socket opt about**********************
    **/

    int       fd;

    socklen_t len;
    struct  sock_opts *ptr;

    for (ptr = sock_optArr; ptr->opt_str != NULL; ptr++ )
    {
        printf("%s: ", ptr->opt_str);
        
        if (ptr->opt_val_str == NULL)
        {
            printf("(undefined)\n");

        } else
        {
            switch (ptr->opt_level)
            {
                case SOL_SOCKET:
                case IPPROTO_IP:
                case IPPROTO_TCP:
                     fd = socket(AF_INET, SOCK_STREAM, 0);
                     break;

#ifdef IPV6

                case IPPROTO_IPV6:
                     fd = socket(AF_INET6, SOCK_STREAM, 0);
                     break;
#endif
#ifdef IPPROTO_SCTP

                case IPPROTO_SCTP:
                     fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
#endif
                default:
                     err_quit("Can't create fd for level %d\n", ptr->opt_level);


            }

            len = sizeof(val);
            if (getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, &len) == -1)  
            {
                err_ret("getsockopt error");

            } else
            {
                printf("default = %s\n", (*ptr->opt_val_str) (&val, len));
            }

            close(fd);

        }
    }


    /*
    * *************************server With for  poll**********************
    **/

    // int i, maxi, listenfd, connfd, sockfd;
    // int nready;
    // ssize_t n;
    // char buf[MAXLINE];
    // socklen_t clilen;
    // struct pollfd client[OPEN_MAX];
    // struct  sockaddr_in cliaddr, servaddr;

    // listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // bzero(&servaddr, sizeof(servaddr));
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(SERV_PORT);

    // bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // listen(listenfd, LISTENQ);

    // client[0].fd = listenfd;
    // client[0].events = POLLRDNORM;
    // for ( i = 1; i < OPEN_MAX; ++i)
    // {
    //     client[i].fd = -1;           /* -1 indicate available entry */
    // }
    // maxi = 0;                        /* max index into client[] array */

    // for (; ;)
    // {
    //     nready = poll(client, maxi, INFTIM);
    //     if (client[0].revents & POLLRDNORM)   /* new client connection */
    //     {
    //         clilen = sizeof(cliaddr);
    //         connfd = accept(listenfd, (SA *) &cliaddr, &clilen);

    //         for ( i =  1; i < OPEN_MAX; ++i)
    //         {
    //             if (client[i].fd < 0)
    //             {
    //                 client[i].fd = connfd;   /* save descriptor */
    //                 break;
    //             }
    //         }

    //         if (i == OPEN_MAX)
    //         {
    //             err_quit("too many clients");
    //         }

    //         client[i].events = POLLRDNORM;
    //         if (i > maxi)
    //         {
    //             maxi = i;             /* max index in clinet[] array */
    //         }
    //         if (--nready <= 0)
    //         {
    //             continue;             /* no more readable descriptors */
    //         }
    //     }

    //     for ( i = 1; i <= maxi; ++i)  /* check all clients for data */
    //     {
    //         if ((sockfd = client[i].fd) < 0)
    //         {
    //             continue;
    //         }
    //         if (client[i].revents & (POLLRDNORM | POLLERR))
    //         {
    //             if ((n = read(sockfd, buf, MAXLINE)) < 0)
    //             {
    //                 if (errno == ECONNRESET)     /* connection reset by client */
    //                 {
    //                     close(sockfd);
    //                     client[i].fd = -1;

    //                 } else
    //                 {
    //                     err_sys("read error");
    //                 }
    //             } else if (n == 0)      /* connection closed by client */
    //             {
    //                 close(sockfd);
    //                 client[i].fd = -1;
    //             } else
    //             {
    //                 writen(sockfd, buf, n);
    //             }

    //             if (--nready <= 0)
    //             {
    //                 break;                     /* no more readable descriptors */
    //             }
    //         }
    //     }
    // }



    /*
    * *************************server With for  select**********************
    **/

    // int  i, maxi, maxfd, listenfd, connfd, sockfd;
    // int nready, client[FD_SETSIZE];
    // ssize_t n;
    // fd_set rset, allset;
    // char buf[MAXLINE];
    // socklen_t clilen;

    // struct sockaddr_in cliaddr, servaddr;
    // listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // bzero(&servaddr, sizeof(servaddr));
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(SERV_PORT);

    // bind(listenfd,(SA *)&servaddr, sizeof(servaddr));
    // listen(listenfd, LISTENQ);

    // maxfd = listenfd;         /* initialize */
    // maxi = -1;                /* index into client[] array */

    // for (int i = 0; i < FD_SETSIZE; ++i)
    // {
    //     client[i] = -1;

    // }

    // FD_ZERO(&allset);
    // FD_SET(listenfd, &allset);

    // for (; ; )
    // {
    //     rset = allset;             /* structure assignment */
    //     nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

    //     if (FD_ISSET(listenfd, &rset))  /* new client connection */
    //     {
    //         clilen = sizeof(cliaddr);

    //         connfd = accept(listenfd, (SA*) &cliaddr, &clilen);

    //         for ( i = 0; i < FD_SETSIZE; ++i)
    //         {
    //             if (client[i] < 0)
    //             {
    //                 client[i] = connfd;  /* save descriptor */
    //                 break;
    //             }
    //         }

    //         if (i == FD_SETSIZE)
    //         {
    //             err_quit("too many clients");
    //         }
    //         FD_SET(connfd, &allset);      /* add new desciptor to set */

    //         if (connfd > maxfd)
    //         {
    //             maxfd = connfd;           /* for select */
    //         }
    //         if (i > maxi)
    //         {
    //             maxi = i;                /* max index in client[] array */
    //         }

    //         if (--nready <= 0)
    //         {
    //             continue;               /* no more readable descriptor */
    //         }

    //     }

    //     for ( i = 0; i <= maxi; ++i)
    //     {
    //         if ((sockfd = client[i]) < 0)
    //         {
    //             continue;
    //         }

    //         if (FD_ISSET(sockfd, &rset))
    //         {
    //             if ((n = read(sockfd, buf, MAXLINE)) == 0)
    //             {
    //                 /* connection closed by client */
    //                 close(sockfd);
    //                 FD_CLR(sockfd, &allset);
    //                 client[i] = -1;
    //             } else
    //             {
    //                 writen(sockfd, buf, n);
    //             }

    //             if (--nready <= 0)
    //             {
    //                 break;                   /* no more readable descriptors */
    //             }
    //         }
    //     }
    // }


    /*
    * *************************server With for child prosesss**********************
    **/

    // int     i, maxi, maxfd, listenfd, connfd, sockfd;
    // pid_t    childpid;
    // socklen_t clilen;
    
    // struct sockaddr_in cliaddr, servaddr;
    
    
    // listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // bzero(&servaddr, sizeof(servaddr));
    
    // servaddr.sin_family = AF_INET;
    
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // servaddr.sin_port = htons(SERV_PORT);
    
    // bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
    // listen(listenfd, LISTENQ);

    // Signal(SIGCHLD, sig_chld);

    
    // for (; ; ) {
        
    //     clilen = sizeof(cliaddr);
        
    //     if ((connfd = accept(listenfd, (SA*)&cliaddr, &clilen)) < 0)
    //     {
    //         if (errno == EINTR)
    //         {
    //             continue;   /* back to for () */
    //         } else
    //         {
    //             err_sys("accept error");
    //         }
    //     }
        


        
    //     if ((childpid = fork()) == 0) {/*child process*/

    //         close(listenfd);           /* close listening socket*/

    //         str_echo(connfd);          /*process the request*/

    //         exit(0);
    //     }
        
    //     close(connfd);/*parent closes connected socket*/
        
    // }
   
    // return 0;
}
