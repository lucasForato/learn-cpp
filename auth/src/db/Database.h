#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

class Database {
  public:
    Database(const char* url);
    int exec(const char* query);
    void close();
  private:
    sqlite3* db;
};

#endif
