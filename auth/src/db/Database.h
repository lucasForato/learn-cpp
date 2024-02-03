#ifndef DATABASE_H
#define DATABASE_H

#include "Model.h"
#include "models/User.h"
#include <sqlite3.h>

class Database {
public:
  Database(const char *url);
  void close();
  Model<User> *user;

private:
  sqlite3 *db;
};

#endif
