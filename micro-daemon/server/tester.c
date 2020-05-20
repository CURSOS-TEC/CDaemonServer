#include "CEServer.h"

int main()
{
    CEServerStr serverStr =
        {
            port_number : 8080
        };
    start_micro_http_server(serverStr);
};