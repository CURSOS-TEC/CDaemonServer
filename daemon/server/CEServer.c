#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include "CEServer.h"

/**
 * Starts a server
 */
int start_server(CEServerStr serverStr)
{
  char server_messages[256] = " you have reacher the server";
  // create the server socket
  int server_socket;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(serverStr.port_number);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // bind the socket to our specified IP and port
  bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
  // 5 as the number of the connections
  listen(server_socket, 5);
  // accept the connection
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);
  send(client_socket, server_messages, sizeof(server_messages), 0);
  printf("Server sending message");
  close(server_socket);
  return 0;
}