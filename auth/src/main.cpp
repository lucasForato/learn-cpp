#include "db/Database.h"
#include <crow/app.h>

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")
  ([]() {
    Database db("cpp.db");

    QueryResponse<User> res = db.exec("SELECT * FROM users");

    for (User user : res.get_data()) {
      cout << "id: " << user.get_id() << endl;
      cout << "username: " << user.get_username() << endl;
      cout << "email: " << user.get_email() << endl;
      cout << "pass: " << user.get_password() << endl;
    }

    return "finished";
  });

  app.port(8000).multithreaded().run();
}
