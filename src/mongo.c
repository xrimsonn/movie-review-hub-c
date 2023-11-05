#include <bson/bson.h>
#include <mongoc/mongoc.h>
#include <stdio.h>
#include <time.h>

int main() {
  char *user = getenv("MONGO_USER");
  char *pass = getenv("MONGO_PASS");

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char date[11];
  strftime(date, sizeof(date), "%Y-%m-%d", tm);

  char conn_string[256];
  sprintf(conn_string, "mongodb://%s:%s@localhost:27017/admin", user, pass);

  mongoc_init();

  mongoc_client_t *client = mongoc_client_new(conn_string);
  mongoc_database_t *database = mongoc_client_get_database(client, "movies");
  mongoc_collection_t *collection =
      mongoc_database_get_collection(database, "logs");
    bson_t *doc = BCON_NEW(
        "name", BCON_UTF8("Chungking Express"), "stars", BCON_INT32(5),
        "description", BCON_UTF8("my fav movie."), "watched",
        BCON_UTF8(date)
    );

  mongoc_collection_insert_one(collection, doc, NULL, NULL, NULL);

  // Obtener el BSON creado
  char *str = bson_as_json(doc, NULL);
  printf("%s\n", str);

  // Libera recursos
  bson_destroy(doc);
  mongoc_collection_destroy(collection);
  mongoc_database_destroy(database);
  mongoc_client_destroy(client);
  mongoc_cleanup();

  return 0;
}
