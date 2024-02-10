#include "usecases/ListUsersUseCase.h"
#include "usecases/SigninUseCase.h"
#include "usecases/SignupUseCase.h"
#include <crow/app.h>

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/health").methods("GET"_method)([]() {
		crow::json::wvalue response({{"status", "ok"}});
		return response;
	});

	CROW_ROUTE(app, "/signup").methods("POST"_method)([](const crow::request& req) {
		crow::json::rvalue body = crow::json::load(req.body);
		if(!body.has("username") || !body.has("email") || !body.has("password"))
		{
			return crow::response(400);
		}

		Result res =
			SignupUseCase::execute({body["username"].s(), body["email"].s(), body["password"].s()});

		return crow::response(res.get_json());
	});

  CROW_ROUTE(app, "/signin").methods("POST"_method)([](const crow::request& req) {
      crow::json::rvalue body = crow::json::load(req.body);
      if(!body.has("email") || !body.has("password"))
      {
          return crow::response(400);
      }

      Result res = SigninUseCase::execute({body["email"].s(), body["password"].s()});
      return crow::response(res.get_json());
        
  });

	CROW_ROUTE(app, "/users").methods("GET"_method)([]() {
		Result res = ListUsersUseCase::execute();
		return crow::response(res.get_json());
	});

	app.port(8000).multithreaded().run();
}
