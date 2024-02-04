#ifndef DATABASE_H
#define DATABASE_H

#include "QueryResponse.h"
#include "models/User.h"
#include <sqlite3.h>
#include <string>

class Database {
public:
  Database(const char *url);

  QueryResponse<User> exec(std::string query);
  static int callback(void *data, int argc, char **argv, char **azColName);
  void close();

private:
  sqlite3 *db;
};

#endif
