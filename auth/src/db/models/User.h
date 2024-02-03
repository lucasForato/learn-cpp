#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
public:
  User(int id, string username, string email, string password);

  int get_id();
  string get_username();
  string get_email();
  string get_password();

private:
  int id;
  string username;
  string password;
  string email;
};

#endif
