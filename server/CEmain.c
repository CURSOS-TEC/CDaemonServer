#include "CEServer.h"

int main()
{
    CEServerStr serverStr =
        {
            port_number : 9001
        };
    start_server(serverStr);
};