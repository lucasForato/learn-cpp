#include "SigninUseCase.h"
#include "../db/Database.h"
#include "../shared/Result.h"
#include <iostream>

using namespace std;

Result SigninUseCase::execute(SigninUseCaseInput input)
{
	vector<string> values = {input.email};

	int rc = Database::exec("SELECT * FROM users WHERE email = ?;", values);
	if(rc == SQLITE_NOTFOUND)
	{
		Result result = Result::error(404, "User not found");
		return result;
	}

	cout << "User found" << rc << endl;
	return Result::ok();
}
