#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

Database::Database(const char *url) {
  int rc = sqlite3_open(url, &db);

  if (rc) {
    cout << "Can't open database\n";
  } else {
    cout << "Opened database successfully\n";
  }
}

int Database::callback(void *data, int argc, char **argv, char **azColName) {

  QueryResponse<User> *response = (QueryResponse<User> *)data;

  int id = 0;
  string username = "";
  string email = "";
  string password = "";
  for (int i = 0; i < argc; i++) {
    if (strcmp(azColName[i], "id") == 0) {
      id = atoi(argv[i]);
    }
    if (strcmp(azColName[i], "username") == 0) {
      username = argv[i];
    }
    if (strcmp(azColName[i], "password") == 0) {
      password = argv[i];
    }
    if (strcmp(azColName[i], "email") == 0) {
      email = argv[i];
    }
  }

  User user(id, username, email, password);
  response->add_data(user);

  return 0;
}

QueryResponse<User> Database::exec(string query) {
  QueryResponse<User> response;

  int rc = sqlite3_exec(db, query.c_str(), callback, &response, nullptr);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  }
  return response;
}

void Database::close() { sqlite3_close(db); }
