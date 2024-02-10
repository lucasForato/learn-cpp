#include "ListUsersUseCase.h"
#include "../db/Database.h"
#include "../db/QueryResponse.h"

Result ListUsersUseCase::execute()
{
	QueryResponse<User> res = Database::exec("SELECT * FROM users;");

	vector<crow::json::wvalue> users = res.dto();

	Result result = Result::success(200, users);

	return result;
}
