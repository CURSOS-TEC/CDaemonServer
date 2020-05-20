#include "CEServer.h"

static const char LOG_FILE[] = "/var/log/ce-image-server.log";
static const char DEV_LOG_FILE[] = "../ce-image-server.log";

/**
 * Saves a log message
 */
void LOG_MESSAGE(char message[])
{
  FILE *fp;
  fp = fopen(LOG_FILE, "a");
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  if (fp)
  {

    printf("\nSaving to file: message: %s\n",message);
    fprintf(fp, "[%s] %d-%02d-%02d %02d:%02d:%02d \n", message, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(fp);
  } else {
    printf("Can't load %s",LOG_FILE);
  }
};

//MHD_USE_POLL_INTERNALLY

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url,
                         const char *method, const char *version,
                         const char *upload_data,
                         size_t *upload_data_size, void **con_cls)
{
  const char *page = "<html><body>Hello, browser!</body></html>";

  struct MHD_Response *response;
  int ret;

  response = MHD_create_response_from_buffer(strlen(page),
                                             (void *)page, MHD_RESPMEM_PERSISTENT);

  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}

int start_micro_http_server(int port)
{
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon(MHD_USE_POLL_INTERNALLY, port, NULL, NULL,
                            &answer_to_connection, NULL, MHD_OPTION_END);
  if (NULL == daemon)
    return 1;
  
  getchar();

  MHD_stop_daemon(daemon);
  return 0;
}
