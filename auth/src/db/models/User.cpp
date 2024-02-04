#include "User.h"
#include "../models/User.h"
#include <sqlite3.h>
#include <string>

User::User(int id, string username, string email, string password)
    : id(id), username(username), email(email), password(password) {}

int User::get_id() { return id; }
string User::get_email() { return email; }
string User::get_password() { return password; }
string User::get_username() { return username; }
