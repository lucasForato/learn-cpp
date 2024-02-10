#include "SignupUseCase.h"
#include "../db/Database.h"
#include "../shared/Result.h"
#include "bcrypt/BCrypt.hpp"
#include <sqlite3.h>

using namespace std;

Result SignupUseCase::execute(SignupInput input)
{
	string hash = BCrypt::generateHash(input.password);

	string sql = "INSERT INTO users (username, email, password)"
				 "VALUES (?, ?, ?);";

	vector<string> values = {input.username, input.email, hash};

	int rc = Database::exec(sql, values);
	if(rc == SQLITE_CONSTRAINT)
	{
		Result result = Result::error(409, "User already exists");
		return result;
	}

	Result result = Result::success(201, "User created successfully");
	return result;
}
