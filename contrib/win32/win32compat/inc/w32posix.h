/*
* Author: Manoj Ampalam <manoj.ampalam@microsoft.com>
*
* Win32 renamed POSIX APIs
*/
#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "defs.h"

/* total fds that can be allotted */
#define MAX_FDS 256  /* a 2^n number */

typedef struct w32_fd_set_ {
	unsigned char bitmap[MAX_FDS >> 3];
}w32_fd_set;

void w32posix_initialize();
void w32posix_done();

/*network i/o*/
int w32_socket(int domain, int type, int protocol);
int w32_accept(int fd, struct sockaddr* addr, int* addrlen);
int w32_setsockopt(int fd, int level, int optname, const char* optval, int optlen);
int w32_getsockopt(int fd, int level, int optname, char* optval, int* optlen);
int w32_getsockname(int fd, struct sockaddr* name, int* namelen);
int w32_getpeername(int fd, struct sockaddr* name, int* namelen);
int w32_listen(int fd, int backlog);
int w32_bind(int fd, const struct sockaddr *name, int namelen);
int w32_connect(int fd, const struct sockaddr* name, int namelen);
int w32_recv(int fd, void *buf, size_t len, int flags);
int w32_send(int fd, const void *buf, size_t len, int flags);
int w32_shutdown(int fd, int how);
int w32_socketpair(int domain, int type, int sv[2]);

/*non-network (file) i/o*/
#define fdopen w32_fdopen
#define fstat w32_fstat

int w32_pipe(int *pfds);
int w32_open(const char *pathname, int flags, ...);
int w32_read(int fd, void *dst, unsigned int max);
int w32_write(int fd, const void *buf, unsigned int max);
int w32_fstat(int fd, struct stat *buf);
int w32_isatty(int fd);
FILE* w32_fdopen(int fd, const char *mode);

/*common i/o*/
#define fcntl w32_fcntl
int w32_close(int fd);
int w32_select(int fds, w32_fd_set* readfds, w32_fd_set* writefds, w32_fd_set* exceptfds, 
	const struct timeval *timeout);
int w32_fcntl(int fd, int cmd, ... /* arg */);
int w32_dup(int oldfd);
int w32_dup2(int oldfd, int newfd);

/* misc */
unsigned int w32_alarm(unsigned int seconds);
typedef void(*sighandler_t)(int);
#define signal w32_signal
#define mysignal w32_signal


/* Shutdown constants */
#define SHUT_WR SD_SEND
#define SHUT_RD SD_RECEIVE
#define SHUT_RDWR SD_BOTH

/* Other constants */
#define IN_LOOPBACKNET	127 /* 127.* is the loopback network */
#define MAXHOSTNAMELEN	64


/* Errno helpers */
#ifndef EXX
#define EXX			WSAEMFILE
#endif
#ifndef EXX1
#define EXX1			WSAENOBUFS
#endif
#ifndef ESOCKTNOSUPPORT
#define	ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#endif
#ifndef ENOTUNREACH
#define ENOTUNREACH		WSAENOTUNREACH
#endif
#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT	        WSAEPFNOSUPPORT
#endif


/* 
 * these routines are temporarily defined here to allow transition 
 * from older POSIX wrapper to the newer one. After complete transition 
 * these should move to a internal header.
 */
int w32_temp_DelChildToWatch(HANDLE processtowatch);
HANDLE w32_fd_to_handle(int fd);
int w32_allocate_fd_for_handle(HANDLE h);
