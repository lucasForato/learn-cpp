#ifndef SIGNUP_USE_CASE_H
#define SIGNUP_USE_CASE_H

#include <sqlite3.h>
#include <string>
#include "../shared/Result.h"

struct SignupInput
{
	std::string username;
	std::string email;
	std::string password;
};

class SignupUseCase
{
public:
	Result execute(SignupInput input);
};

#endif
