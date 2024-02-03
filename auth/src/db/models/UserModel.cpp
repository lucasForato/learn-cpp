#import "UserModel.h"
#include "../QueryResponse.h"
#include <iostream>

QueryResponse<User> UserModel::callbackImpl(void *data, int argc, char **argv,
                                            char **azColName) {
  std::cout << "USER Callback\n";
  QueryResponse<User> *result = static_cast<QueryResponse<User> *>(data);

  for (int i = 0; i < argc; i++) {
    cout << argv[i] << endl;
  }

  return *result;
}

QueryResponse<User> UserModel::select(std::string query, sqlite3 &db) {

  QueryResponse<User> result;

  int rc =
      sqlite3_exec(&db, query.c_str(), UserModel::callback, &result, nullptr);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Error executing query\n");
  } else {
    fprintf(stdout, "Query executed successfully\n");
  }

  return result;
}
