#include "SigninUseCase.h"
#include "../db/Database.h"
#include "../shared/Result.h"
#include "bcrypt/BCrypt.hpp"

using namespace std;

Result SigninUseCase::execute(SigninUseCaseInput input)
{
	vector<string> values = {input.email};

	QueryResponse<User> user = Database::select("SELECT * FROM users WHERE email = ?;", values);

  string pass = user.get_data()[0].get_password();

  bool does_pass_match = BCrypt::validatePassword(input.password, pass);

  if (!does_pass_match)
  {
    return Result::error(401, "Invalid email or password");
  }

	return Result::success(200, user.dto());
}
