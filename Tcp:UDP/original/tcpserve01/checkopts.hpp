#include "unp.hpp"
#include <netinet/tcp.h>

union val{
	int               i_val;
	long              l_val;
	struct  linger    linger_val;
	struct  timeval   timeval_val;
} val;

static char *sock_str_flag(union val*ptr, int len);
static char *sock_str_int(union val*ptr, int len);
static char *sock_str_linger(union val*ptr, int len);
static char *sock_str_timeval(union val*ptr, int len);

struct  sock_opts
{
	const char  *opt_str;
	int   opt_level;
	int   opt_name;
	char  *(* opt_val_str) (union val *, int);
	
};
 struct sock_opts sock_optArr[] = {

	{"SO_BROADCAST",                   SOL_SOCKET, SO_BROADCAST,      sock_str_flag},
	{"SO_DEBUG",                       SOL_SOCKET, SO_DEBUG,          sock_str_flag},
	{"SO_DONTROUTE",                   SOL_SOCKET, SO_DONTROUTE,      sock_str_flag},
	{"SO_ERROR",                       SOL_SOCKET, SO_ERROR,          sock_str_int},
	{"SO_KEEPALIVE",                   SOL_SOCKET, SO_KEEPALIVE,      sock_str_flag},
	{"SO_LINGER",                      SOL_SOCKET, SO_LINGER,         sock_str_linger},
	{"SO_OOBINLINE",                   SOL_SOCKET, SO_OOBINLINE,      sock_str_flag},
	{"SO_RCVBUF",                      SOL_SOCKET, SO_RCVBUF,         sock_str_int},
	{"SO_SNDBUF",                      SOL_SOCKET, SO_SNDBUF,         sock_str_int},
	{"SO_RCVLOWAT",                    SOL_SOCKET, SO_RCVLOWAT,       sock_str_int},
	{"SO_SNDLOWAT",                    SOL_SOCKET, SOL_SOCKET,        sock_str_int},
	{"SO_RCVTIMEO",                    SOL_SOCKET, SO_RCVTIMEO,       sock_str_timeval},
	{"SO_SNDTIMEO",                    SOL_SOCKET, SO_SNDTIMEO,       sock_str_timeval},
	{"SO_REUSEADDR",                   SOL_SOCKET, SO_REUSEADDR,      sock_str_flag},
#ifdef SO_REUSEPORT
	{"SO_REUSEPORT",                   SOL_SOCKET, SO_REUSEPORT,      sock_str_flag},
#else
	{"SO_REUSEPORT",                   0,           0,                 NULL},
#endif
	{"SO_TYPE",                        SOL_SOCKET, SO_TYPE,           sock_str_int},
	{"SO_USELOOPBACK",                 SOL_SOCKET, SO_USELOOPBACK,    sock_str_flag},
	{"IP_TOS",                         IPPROTO_IP, IP_TOS,            sock_str_int},
	{"IP_TTL",                         IPPROTO_IP, IP_TTL,            sock_str_int},
	// {"IPV6_DONTFRAG",                  IPPROTO_IPV6, IPV6_DONTFRAG,   sock_str_flag},
	{"IPV6_UNICAST_HOPS",              IPPROTO_IPV6, IPV6_UNICAST_HOPS, sock_str_int},
	{"IPV6_V6ONLY",                    IPPROTO_IPV6, IPV6_V6ONLY,     sock_str_flag},
	{"TCP_MAXSEG",                     IPPROTO_TCP, TCP_MAXSEG,       sock_str_int},
	{"TCP_NODELAY",                    IPPROTO_TCP, TCP_NODELAY,      sock_str_flag},
	// {"SCTP_AUTOCLOSE",                 IPPROTO_SCTP, SCTP_AUTOCLOSE,  sock_str_int},
	// {"SCTP_MAXBURST",                  IPPROTO_SCTP, SCTP_MAXBURST,   sock_str_int},
	// {"SCTP_MAXSEG",                    IPPROTO_SCTP, SCTP_MAXSEG,     sock_str_int},
	// {"SCTP_NODELAY",                   IPPROTO_SCTP, SCTP_NODELAY,    sock_str_flag},
	{NULL,                             0,            0,               NULL }

};


static char strres[128];

static char *sock_str_flag(union val*ptr, int len)
{
	if (len != sizeof(int))
	{
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
		
	} else
	{
		snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off" : "on");

	}

	return(strres);

}
static char *sock_str_int(union val*ptr, int len)
{

	if (len != sizeof(int))
	{
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
		
	} else
	{
		snprintf(strres, sizeof(strres), "%d", ptr->l_val);

	}

	return (strres);

}
static char *sock_str_linger(union val*ptr, int len)
{

	if (len != sizeof(struct linger))
	{
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct linger)", len);
		
	} else
	{
		snprintf(strres, sizeof(strres), "%ld l_onoff %ld l_linger", ptr->linger_val.l_onoff,ptr->linger_val.l_linger);

	}
	return (strres);

}

static char *sock_str_timeval(union val*ptr, int len)
{


	if (len != sizeof(struct timeval))
	{
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct timeval)", len);
		
	} else
	{
		snprintf(strres, sizeof(strres), "%ld seconds %ld microseconds", ptr->timeval_val.tv_sec,ptr->timeval_val.tv_usec);

	}

	return (strres);

}
