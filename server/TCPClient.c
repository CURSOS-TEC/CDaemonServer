#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
int main()
{
    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); // using TCP as default

    //address structure specification
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9007);
    server_address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

    // connection to the server
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // check if there is an error
    if (connection_status == -1)
    {
        printf("There is an error during the connection\n");
    }

    // receive data
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print out the server's response
    printf("The server sent the data: %s\n", server_response);

    //and then close the socket
    close(network_socket);

    return 0;
}