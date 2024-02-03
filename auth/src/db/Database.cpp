#include "Database.h"
#include "Result.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

Database::Database(string url) {
  int rc = sqlite3_open(url.c_str(), &db);

  if (rc) {
    cout << "Can't open database\n";
  } else {
    cout << "Opened database successfully\n";
  }
}

template <typename T>
static int callback(void *data, int argc, char **argv, char **azColName) {
  Result<T> *result = static_cast<Result<T> *>(data);

  T obj;
  for (int i = 0; i < argc; i++) {
    switch (i) {
    case 0:
      obj.member1 = argv[i] ? atoi(argv[i]) : 0;
      break;
    case 1:
      obj.member2 = argv[i] ? argv[i] : "";
      break;
    }
  }

  result->add_data(obj);

  return 0;
}

template <typename T> Result<T> Database::exec(string query) {
  char *zErrMsg = nullptr;

  Result<T> result;
  int rc = sqlite3_exec(db, query.c_str(), callback<T>, &result, &zErrMsg);

  if (rc != SQLITE_OK) {
    result.set_error(zErrMsg);
    sqlite3_free(zErrMsg);
  }

  return result;
}

void Database::close() { sqlite3_close(db); }
