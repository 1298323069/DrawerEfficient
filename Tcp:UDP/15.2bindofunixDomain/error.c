//
//  error.c
//  tesetfile
//
//  Created by 梁坤 on 17/6/10.
//  Copyright © 2017年 Liangkun. All rights reserved.
//

#include "unp.h"
#include <stdarg.h>      /* ANSI C header file */
#include <syslog.h>      /* for syslog() */

int daemon_proc;

static void err_doit(int  errnoflag, int level, const char *fmt, va_list ap)
{
    int      errno_save, n;
    char     buf[MAXLINE + 1];
    
    errno_save = errno;  /* value caller might want printed */
#ifdef HAVE_VSNPRINTF
    vsnprintf(buf, MAXLINE, fmt, ap);        /* safe */
#endif
    n = strlen(buf);
    if (errnoflag)
        snprintf(buf + n, MAXLINE -n, ": %s",strerror(errno_save));
    strcat(buf,"\n");
    
    if (daemon_proc) {
        syslog(level, buf);
    } else {
        fflush(stdout);      /* in case stdout and stderr are the same */
        fputs(buf,stderr);
        fflush(stderr);
    }
    
    return;
}

void err_ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
    
}

void err_sys(const char *fmt, ...)
{
    va_list  ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

void err_dump(const char *fmt, ...)
{
    va_list  ap;
    
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort();
}

void err_msg(const  char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

void err_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    
    va_end(ap);
    exit(1);

}



























