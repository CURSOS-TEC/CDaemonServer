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
    pid_t pid, sid;
    pid = fork();

    /* Fork off the parent process */
    if (pid < 0)
    {
        /* Log failure (use syslog if possible) */
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
           we can exit the parent process. */
    if (pid > 0)
    {
        printf(" PID: %d \n", pid);
        exit(EXIT_SUCCESS);
    }
    /* Open any logs here */

    /* Change the file mode mask */
    umask(0); // By setting the umask to 0, we will have full access to the files generated by the daemon.

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0)
    {
        /* Log any failure */
        exit(EXIT_FAILURE);
    }
    printf(" SID: %d \n", sid);

    /* Change the current working directory */
    if ((chdir("/")) < 0)
    {
        printf(" EXIT FAILURE");
        /* Log any failure here */
        exit(EXIT_FAILURE);
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    /* Close out the standard file descriptors */
    /**
     * The classic guide to POSIX programming "Advanced programming in UNIX environment" states:
     * When a process terminates, all of its open files are closed automatically by the kernel.
     * Many programs take advantage of this fact and don't explicitly close open files.
     */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */
    FILE *fp;
    int i;

    /* The Big Loop */

    while (1)
    {
        /* Do some task here ... */
        sleep(5); /* wait 5 seconds */
                  /* open the file for writing*/
        fp = fopen("/home/gotouch/tec/so_projects/daemon/testFile", "a");

        /* write 10 lines of text into the file stream*/
        for (i = 0; i < 10; i++)
        {
            // time_t t = time(NULL);
            // printf(" PID: %d \n", pid);
            // struct tm tm = *localtime(&t);
            // fprintf(fp, "now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
            // sleep(1);
            // // fprintf(fp, "This is line %d  written by PID: %i \n", i + 1, pid);

            CEServerStr serverStr =
                {
                    port_number : 9001
                };
            start_server(serverStr);
        }

        /* close the file*/
        fclose(fp);
    }

    return 0;
}
