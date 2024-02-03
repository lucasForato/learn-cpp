#include "Database.h"
#include "models/User.h"
#include "models/UserModel.h"
#include <iostream>
#include <sqlite3.h>

using namespace std;

Database::Database(const char *url) {
  int rc = sqlite3_open(url, &db);

  User user = new UserModel(db);

  if (rc) {
    cout << "Can't open database\n";
  } else {
    cout << "Opened database successfully\n";
  }
}

void Database::close() { sqlite3_close(db); }
