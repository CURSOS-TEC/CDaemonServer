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
#include <syslog.h>
#include "ImageProcessor.h"
/**
 * For Post constants
 */
#define POSTBUFFERSIZE 512
#define MAXNAMESIZE 20
#define MAXANSWERSIZE 512

#define MAXCLIENTS 2
static unsigned int nr_of_uploading_clients = 0;

#define GET 0
#define POST 1

FILE *fp;

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

/**
 * Connection struct
 */
struct connection_info_struct
{
    char *pathfile;
    int connectiontype;
    const char *answerstring;
    int answercode;
    struct MHD_PostProcessor *postprocessor;
    FILE *fp;
};

/**
 * Iterates over post message
 */
static int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind,
                        const char *key, const char *filename, const char *content_type,
                        const char *transfer_encoding, const char *data,
                        uint64_t off, size_t size);

/**
 * Sends a page
 */
static int send_page(struct MHD_Connection *connection, const char *page, int status_code);

/**
 * Callback used when a connection happens
 */
static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls);

/**
 * Logs a message
 */
void LOG_MESSAGE(char message[]);

/**
 * 
 */
int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url,
                         const char *method, const char *version,
                         const char *upload_data,
                         size_t *upload_data_size, void **con_cls);

/**
 * starts a micro http server
 */
int start_micro_http_server(int port, struct MHD_Daemon *daemon);

/**
 * Stops a micro http server
 */
int stop_micro_http_server(struct MHD_Daemon *daemon);
#endif
