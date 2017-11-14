#include "unp.h"
char *sock_ntop(const struct sockaddr *sa, socklen_t len)
{
    char    portstr[8];
    static char str[128];
    switch (sa->sa_family) {
        case AF_INET:{
            struct sockaddr_in  *sin = (struct sockaddr_in *)sa;
            if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                printf("return null");
            
                return(NULL);
            if (ntohs(sin->sin_port) != 0) {
                snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
                strcat(str, portstr);
            }
            return str;
        }
    }
    
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr,socklen_t servlen)
{
    
    
    int        n;
    char       sendline[MAXLINE],recvline[MAXLINE + 1];
    
    connect(sockfd, (SA *) pservaddr, servlen);
    
    
    while (fgets(sendline,MAXLINE,fp) != NULL) {
        write(sockfd, sendline, strlen(sendline));
        
        n = read(sockfd, recvline, MAXLINE);
        
        recvline[n] = 0;  /* null terminate */
        
        fputs(recvline,stdout);
    }
    
    
    
    
    

}
int main(int argc, const char ** argv) {
    
   
    int           sockfd;
    struct sockaddr_in servaddr;
    
    if (argc != 2)
//        err_quit("usage: udpcli <IPaddress>");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));
    exit(0);
}
