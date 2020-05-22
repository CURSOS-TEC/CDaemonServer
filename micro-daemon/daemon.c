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
#include "config/config.h"
/** This program test an image reader */
int main(int argc, char **argv)
{

    // STARTING SERVER
    printf("Iniciando el Servidor Image\n");

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

    // /* Close out the standard file descriptors */
    // close(STDIN_FILENO);
    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */

    /* The Big Loop */
    printf("Server using microhttpd\n");
    LOG_MESSAGE("Try to init server");
    // CONSTANTES CONFIGURABLES
    int PORT, SLEEP_TIME, ACTIVE;
    // GETTING CONFIG
    PORT = get_port_config();
    printf("Puerto leído: %d\n", PORT);
    SLEEP_TIME = get_sleep_time();
    printf("TIEMPO LEÍDO: %d\n", SLEEP_TIME);
    struct MHD_Daemon *daemon;
    ACTIVE = start_micro_http_server(PORT, daemon);
    if (!ACTIVE)
    {
        printf("ERROR: No se pudo inicializar el servidor\n");
        return 1;
    }
    update_active(ACTIVE);

    while (ACTIVE)
    {
        LOG_MESSAGE("Server is running");
        ACTIVE = check_active();
        sleep(SLEEP_TIME);
    }
    printf("Terminando el Image Server ...");
    stop_micro_http_server(daemon);
    printf("Finalizado.\n");
    exit(EXIT_SUCCESS);
    return 0;
}
