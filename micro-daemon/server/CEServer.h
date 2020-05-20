#ifndef CEServer_HEADER_FILE
#define CEServer_HEADER_FILE
#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>
#include <sys/select.h>
#include <time.h>
/**
 * This is an abstraction of the CE server which is going to be the server block
 */
typedef struct
{
    /**
     * The port number
     */
    int port_number;
} CEServerStr;
void LOG_MESSAGE(char message[]);
/**
 * 
 */ 
int answer_to_connection (void *cls, struct MHD_Connection *connection,
                          const char *url,
                          const char *method, const char *version,
                          const char *upload_data,
                          size_t *upload_data_size, void **con_cls);

/**
 * 
 */ 
void start_micro_http_server (int port,struct MHD_Daemon *daemon);

/**
 */ 
void  stop_micro_http_server(struct MHD_Daemon *daemon);
#endif
