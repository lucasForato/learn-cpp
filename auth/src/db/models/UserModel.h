#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "../Model.h"
#include "./User.h"
#include <sqlite3.h>
#include <string>

using namespace std;

class UserModel : public Model<User> {
public:
  UserModel(sqlite3 &db);
  QueryResponse<User> select(std::string query, sqlite3 &db);
  static int callback(void *data, int argc, char **argv, char **azColName) {
    Model<User> *instance = static_cast<Model<T> *>(data);
    instance->callbackImpl(argc, argv, azColName);
    return 0;
  };

private:
  sqlite3 *db;
  QueryResponse<User> callbackImpl(void *data, int argc, char **argv,
                                   char **azColName);
};

#endif
