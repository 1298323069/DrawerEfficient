#ifndef readline_hpp
#define readline_hpp
#include "unp.hpp"

ssize_t readline(int fd, char *vptr, size_t maxlen);
ssize_t readn(int fd, char *vptr, size_t n);
ssize_t  writen(int fd, const char *vptr, size_t n);
#endif