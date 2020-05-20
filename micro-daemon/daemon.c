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
    /* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
           we can exit the parent process. */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0)
    {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0)
    {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */

    /* The Big Loop */
    printf("Server using microhttpd\n");
    LOG_MESSAGE("Try to init server");
    struct MHD_Daemon *daemon;
    start_micro_http_server(8080,daemon);

    while (1)
    {
        LOG_MESSAGE("Server is running");
        sleep(1);
    }
    stop_micro_http_server(daemon);
    exit(EXIT_SUCCESS);
    return 0;
}
