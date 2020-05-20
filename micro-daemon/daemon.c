// http://www.netzmafia.de/skripten/unix/linux-daemon-howto.html
// https://www.geeksforgeeks.org/understanding-extern-keyword-in-c/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include "server/CEServer.h"
/** This program test an image reader */
int main(int argc, char **argv)
{ 
    printf("Server using microhttpd\n");
    LOG_MESSAGE("Try to init server");  
    start_micro_http_server(8080);
    /**
     * The classic guide to POSIX programming "Advanced programming in UNIX environment" states:
     * When a process terminates, all of its open files are closed automatically by the kernel.
     * Many programs take advantage of this fact and don't explicitly close open files.
     */
    LOG_MESSAGE("Server finished");
    return 0;
}
