//
//  unp.c
//  UnixNetAbout
//
//  Created by 梁坤 on 17/4/15.
//  Copyright © 2017年 Liangkun. All rights reserved.
//

#include "unp.hpp"
#include "error.hpp"
#include "wrapsock.hpp"

int Socket(int family, int type, int protocol)
{
	int n;
	if ((n = socket(family, type, protocol)) < 0)
	{
		err_sys("socket error");
	}

	return n;
}
