//
//  unp.c
//  UnixNetAbout
//
//  Created by 梁坤 on 17/4/15.
//  Copyright © 2017年 Liangkun. All rights reserved.
//

#include "unp.hpp"
void sig_chld(int signo)
{
	pid_t pid;
	int   stat;

	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		printf("child %d terminated\n", pid);
	}
	return;
}
