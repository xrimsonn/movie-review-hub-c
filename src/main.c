#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
  const char *page = "<html><body>Hello, World!</body></html>";
  struct MHD_Response *response;

  response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                             MHD_RESPMEM_PERSISTENT);
  int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}

int main(int argc, char const *argv[]) {
  struct MHD_Daemon *daemon;
  daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 2264, NULL, NULL,
                            &request_handler, NULL, MHD_OPTION_END);

  if (daemon == NULL) {
    fprintf(stderr, "Error starting the server.\n");
    return 1;
  }

  printf("Server is running at http://localhost:2264\n");

  getchar();

  MHD_stop_daemon(daemon);

  return 0;
}
