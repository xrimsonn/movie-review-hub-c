#include "handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *load_file(const char *filename) {
  FILE *htmlFile = fopen(filename, "r");
  if (htmlFile == NULL) {
    perror("Error opening file");
    return NULL;
  }

  fseek(htmlFile, 0, SEEK_END);
  long fileSize = ftell(htmlFile);
  rewind(htmlFile);

  char *buffer = (char *)malloc(sizeof(char) * (fileSize + 1));
  if (buffer == NULL) {
    printf("Could not allocate memory for the buffer\n");
    fclose(htmlFile);
    return NULL;
  }

  size_t result = fread(buffer, 1, fileSize, htmlFile);
  if (result != fileSize) {
    printf("Error\n");
    free(buffer);
    fclose(htmlFile);
    return NULL;
  }

  buffer[fileSize] = '\0';
  fclose(htmlFile);
  return buffer;
}

enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
  char *page = load_file("pages/index.html");
  if (page == NULL) {
    return MHD_NO;
  }

  

  struct MHD_Response *response;

  response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                             MHD_RESPMEM_PERSISTENT);
  int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}