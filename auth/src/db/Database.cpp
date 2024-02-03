#include "Database.h"
#include <sqlite3.h>
#include <iostream>

using namespace std;

Database::Database(const char* url) {
  int rc = sqlite3_open(url, &db);

   if( rc ) {
      cout << "Can't open database\n";
   } else {
      cout << "Opened database successfully\n";
   }
}

static int callback(void *data, int argc, char **argv, char **azColName) {
  return 0;
}

int Database::exec(const char* query) {
  char *zErrMsg = 0;

  int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);

  if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Query executed successfully\n");
   }

  return rc;
}

void Database::close() {
  sqlite3_close(db);
}

