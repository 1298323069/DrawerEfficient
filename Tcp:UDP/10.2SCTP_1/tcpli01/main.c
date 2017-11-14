#include "unp.h"


void sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen)
{
    struct sockaddr_in  peeraddr;
    struct sctp_sendrcvinfo sri;
    char   sendline[MAXLINE], recvline[MAXLINE];
    socklen_t   len;
    int out_sz, rd_sz;
    int msg_flags;
    
    bzero(&sri, sizeof(sri));
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        if (sendline[0] != '[') {
            printf("Error, line must be of the form '[streanum] text'\n");
            continue;
        }
        sri.sinfo_stream = strtol(&sendline[1], NULL, 0);
        out_sz = strlen(sendline);
        sctp_sendmsg(sock_fd, recvline, sizeof(recvline),(SA *)&peeraddr, &len, &sri, &msg_flags);
        printf("From str: %d seq: %d (assoc:0x%x):",sri.sinfo_stream,sri.sinfo_ssn,(u_int)sri.sinfo_assoc_id);
        printf("%.*s", rd_sz, recvline);
    }

}
int main(int argc, const char ** argv) {
    
    int sockfd;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if (argc != 2)
        
        printf("usage: a.out <IPaddress>");
    
    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0)
          printf("socket error");

    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        printf("inet_pton error for %s",argv[1]);

    if (connect(sockfd,(SA *) &servaddr, sizeof(servaddr)) < 0)
        printf("connect error\n");
    
    str_cli(stdin,sockfd);
    
    exit(0);

}
