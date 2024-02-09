#include "usecases/ListUsersUseCase.h"
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
		// -- validation -----------------------------------------------------------
		crow::json::rvalue body = crow::json::load(req.body);
		if(!body.has("username") || !body.has("email") || !body.has("password"))
		{
			return crow::response(400);
		}

		// -- execution ------------------------------------------------------------
		SignupUseCase usecase;
		Result res =
			usecase.execute({body["username"].s(), body["email"].s(), body["password"].s()});

		return crow::response(res.get_json());
	});

	CROW_ROUTE(app, "/users").methods("GET"_method)([]() {
		ListUsersUseCase usecase;
		Result res = usecase.execute();
		return crow::response(res.get_json());
	});

	app.port(8000).multithreaded().run();
}
