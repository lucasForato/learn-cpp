#include "QueryResponse.h"
#include "models/User.h"
#include <vector>

template <> QueryResponse<User>::QueryResponse() : data({}), error(nullptr) {}

template <> void QueryResponse<User>::add_data(User d) { data.push_back(d); }
