#ifndef SIGN_IN_USE_CASE_H
#define SIGN_IN_USE_CASE_H

#include "../shared/Result.h"
#include <string>

struct SigninUseCaseInput
{
  std::string email;
  std::string password; 
};

class SigninUseCase 
{
  public:
    static Result execute(SigninUseCaseInput input);
};

#endif
