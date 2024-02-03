#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
public:
  User(int id, string username, string email, string password)
    : id(id), username(username), email(email), password(password) {}

  int get_id() { return this->id; }
  string get_username() { return this->username; }
  string get_email() { return this->email; }
  string get_password() { return this->password; }

private:
  int id;
  string username;
  string password;
  string email;
};

#endif
