#ifndef CEServer_HEADER_FILE
#define CEServer_HEADER_FILE
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
 * Starts a server
 */ 
int start_server(CEServerStr serverStr);

#endif
