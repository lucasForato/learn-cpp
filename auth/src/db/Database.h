#ifndef DATABASE_H
#define DATABASE_H

#include "QueryResponse.h"
#include "models/User.h"
#include <sqlite3.h>
#include <string>

class Database {
public:
  static sqlite3* open(std::string path);
  static QueryResponse<User> exec(std::string query);
  static int exec(std::string query, vector<string> &values);
  
  static int callback(void *data, int argc, char **argv, char **azColName);
};

#endif
