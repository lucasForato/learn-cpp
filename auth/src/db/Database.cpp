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
  int rc = sqlite3_exec(db, query, callback, nullptr, nullptr);

  if( rc != SQLITE_OK ){
      fprintf(stderr, "Error executing query\n");
   } else {
      fprintf(stdout, "Query executed successfully\n");
   }

  return rc;
}

void Database::close() {
  sqlite3_close(db);
}

