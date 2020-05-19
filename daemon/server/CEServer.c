#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> // for close
#include <string.h>
#include "CEServer.h"
static const char LOG_FILE[] = "/var/log/ce-image-server.log";

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
  while (1)
  {
    client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, server_messages, sizeof(server_messages), 0);
    printf("Server sending message");
    close(server_socket);
  }

  return 0;
}

/**
 * Starts an http server connection
 */
int start_http_server(CEServerStr serverStr)
{
  FILE *html_data;
  html_data = fopen("index.html", "r");
  char response_data[8096];
  fgets(response_data, 8096, html_data);
  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  strcat(http_header, response_data);

  //creates a server socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  // server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(serverStr.port_number);
  server_address.sin_addr.s_addr = INADDR_ANY;
  bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
  listen(server_socket, 5);
  int client_socket;
  FILE *fp;
  fp = fopen(LOG_FILE, "a");
  fprintf(fp, "Server initialize");
  fclose(fp);
  while (1)
  {
    client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, http_header, sizeof(http_header), 0);
    close(client_socket);
  }
  return 0;
}