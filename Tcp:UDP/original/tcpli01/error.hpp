//
//  unp.h
//  UnixNetAbout
//
//  Created by 梁坤 on 17/4/15.
//  Copyright © 2017年 Liangkun. All rights reserved.
//
#ifndef error_hpp
#define error_hpp
void err_quit(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...); 
#endif