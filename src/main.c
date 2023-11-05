#include <microhttpd.h>
#include <stdio.h>
#include "handler.h"


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
