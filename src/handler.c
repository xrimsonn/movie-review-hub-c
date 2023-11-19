#include "handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http_parser.h"

http_parser_settings settings;
http_parser parser;
char *page;
char *load_page(const char *filename) {
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

int on_url(http_parser *parser, const char *at, size_t length) {
  char url[length + 1];
  strncpy(url, at, length);
  url[length] = '\0';

  if (strcmp(url, "/") == 0) {
    page = load_page("pages/index.html");
    if (page == NULL) {
      return MHD_NO;
    }
    struct MHD_Response *response;
  } else if (strcmp(url, "/index") == 0) {
    page = load_page("pages/index.html");
    if (page == NULL) {
      return MHD_NO;
    }
    struct MHD_Response *response;
  } else if (strcmp(url, "/reviews") == 0) {
    // TODO
  } else if (strcmp(url, "/create") == 0) {
    // TODO
  } else if (strcmp(url, "/delete") == 0) {
    // TODO
  } else if (strcmp(url, "/update") == 0) {
    // TODO
  } else {
    page = load_page("pages/404.html");
    if (page == NULL) {
      return MHD_NO;
    }
    struct MHD_Response *response;
  }
  return 0;
}

void setup_http_parser() {
  settings.on_url = on_url;
  http_parser_init(&parser, HTTP_REQUEST);
  parser.data = NULL;
}

enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
  setup_http_parser();

  char request[1024];
  strcpy(request, method);
  strcat(request, " ");
  strcat(request, url);
  strcat(request, " ");
  strcat(request, version);
  strcat(request, "\r\nHost: localhost\r\n\r\n");

  http_parser_execute(&parser, &settings, request, strlen(request));

  struct MHD_Response *response;

  if (page == NULL) {
    return MHD_NO;
  }

  response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                             MHD_RESPMEM_PERSISTENT);
  int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  return ret;
}
