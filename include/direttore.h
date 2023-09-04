#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUF_SIZE 128
#define PATH_SIZE 128
#define SOCKNAME "./unix_socket"
#define N 100

#define IFERROR(s,v,m) if((s)==v) {perror(m); exit(errno);}
#define IFERROR3(s,v,m,c) if((s)==v) {perror(m); c;}
#define IFERRORM1(s,m) if((s)==-1) {perror(m); exit(errno);}
#define IFERROR3C(s,m,c) if((s)==-1) {perror(m); c;}

#define WRITE(m) IFERROR(write(STDOUT,m,strlen(m)), m);
#define WRITELN(m) WRITE(m);WRITE("\n");
