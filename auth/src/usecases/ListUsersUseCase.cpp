#include "ListUsersUseCase.h"
#include "../db/Database.h"
#include "../db/QueryResponse.h"

Result ListUsersUseCase::execute() 
{ 
    Database db("cpp.db");

		string sql = "SELECT * FROM users;";
		QueryResponse<User> res = db.exec(sql);

		vector<crow::json::wvalue> users = res.dto();

    Result result = Result::success(200, users);

    return result;
}
