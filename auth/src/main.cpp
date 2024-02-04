#include "db/Database.h"
#include "db/QueryResponse.h"
#include <crow/app.h>

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/health")
  ([]() {
    crow::json::wvalue response({{"status", "ok"}});
    return response;
  });

  CROW_ROUTE(app, "/signup")
  ([]() {
    Database db("cpp.db");

    string sql = "INSERT INTO users (id, username, email, password) VALUES (?, "
                 "?, ?, ?);";
    vector<string> values = {"3", "test", "test", "test"};

    int res = db.exec(sql, values);

    crow::json::wvalue response({{"status", 200}});

    return response;
  });

  CROW_ROUTE(app, "/users")
  ([]() {
    Database db("cpp.db");

    string sql = "SELECT * FROM users;";
    QueryResponse<User> res = db.exec(sql);

    vector<crow::json::wvalue> users = res.dto();

    crow::json::wvalue response({{"status", 200}, {"users", users}});
    return response;
  });

  app.port(8000).multithreaded().run();
}
