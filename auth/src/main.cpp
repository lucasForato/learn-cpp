#include "db/Database.h"
#include "db/QueryResponse.h"
#include <crow/app.h>

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/health").methods("GET"_method)([]() {
    crow::json::wvalue response({{"status", "ok"}});
    return response;
  });

  CROW_ROUTE(app, "/signup")
      .methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue body = crow::json::load(req.body);

        // validation
        if (!body.has("username") || !body.has("email") ||
            !body.has("password")) {
          return crow::response(400);
        }

        string username = body["username"].s();
        string email = body["email"].s();
        string password = body["password"].s();

        Database db("cpp.db");

        string sql = "INSERT INTO users (username, email, password)"
                     "VALUES (?, ?, ?);";

        vector<string> values = {body["username"].s(), body["email"].s(),
                                 body["password"].s()};

        int res = db.exec(sql, values);

        crow::json::wvalue response({{"status", 200}});

        return crow::response(response);
      });

  CROW_ROUTE(app, "/users").methods("GET"_method)([]() {
    Database db("cpp.db");

    string sql = "SELECT * FROM users;";
    QueryResponse<User> res = db.exec(sql);

    vector<crow::json::wvalue> users = res.dto();

    crow::json::wvalue response({{"status", 200}, {"users", users}});
    return response;
  });

  app.port(8000).multithreaded().run();
}
