#ifndef LIST_USERS_USE_CASE_H
#define LIST_USERS_USE_CASE_H

#include <sqlite3.h>
#include "../shared/Result.h"

class ListUsersUseCase 
{
public:
	Result execute();
};

#endif
