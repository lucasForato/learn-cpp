#include "QueryResponse.h"
#include "models/User.h"
#include <vector>
#include <crow/app.h>

template <> QueryResponse<User>::QueryResponse() : data({}), error(nullptr) {}

template <> void QueryResponse<User>::add_data(User d) { data.push_back(d); }

template <>
std::vector<crow::json::wvalue> QueryResponse<User>::dto() {
    std::vector<crow::json::wvalue> res = {};

    for (auto& d : data) {
        crow::json::wvalue user;
        user["id"] = d.get_id();
        user["username"] = d.get_username();
        user["email"] = d.get_email();
        user["password"] = d.get_password();
        res.push_back(user);
    }

    return res;
}
