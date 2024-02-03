#ifndef MODEL_H
#define MODEL_H

#include "QueryResponse.h"
#include <sqlite3.h>
#include <string>

template <typename T> class Model {
public:
  virtual QueryResponse<T> select(std::string query) = 0;
  static int callback(void *data, int argc, char **argv,
                                   char **azColName) {
    Model<T> *instance = static_cast<Model<T> *>(data);
    instance->callbackImpl(data, argc, argv, azColName);
    return 0;
  }

  virtual ~Model() = default;

private:
  virtual QueryResponse<T> callbackImpl(void *data, int argc, char **argv,
                                        char **azColName) = 0;
};

#endif
