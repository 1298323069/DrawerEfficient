#include "unp.h"
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
int main(int argc, const char ** argv) {
    
   
    int           sockfd;
    socklen_t     len;
    struct sockaddr_in cliaddr, servaddr;
    
    if (argc != 2)
        printf("argument error");
        
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    
    len = sizeof(cliaddr);
    
    getsockname(sockfd, (SA*)&cliaddr, &len);
    
    printf("local address %s\n", sock_ntop((SA*) &cliaddr, len));
    
    exit(0);
}
