#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

sqlite3* Database::open(std::string path)
{
	sqlite3* db;
	int rc = sqlite3_open("cpp.db", &db);

	if(rc)
	{
		cout << "Can't open database\n";
	}
	else
	{
		cout << "Opened database successfully\n";
	}
	return db;
}

int Database::callback(void* data, int argc, char** argv, char** azColName)
{

	QueryResponse<User>* response = (QueryResponse<User>*)data;

	int id = 0;
	string username = "";
	string email = "";
	string password = "";
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(azColName[i], "id") == 0)
		{
			id = atoi(argv[i]);
		}
		if(strcmp(azColName[i], "username") == 0)
		{
			username = argv[i];
		}
		if(strcmp(azColName[i], "password") == 0)
		{
			password = argv[i];
		}
		if(strcmp(azColName[i], "email") == 0)
		{
			email = argv[i];
		}
	}

	User user(id, username, email, password);
	response->add_data(user);

	return 0;
}

QueryResponse<User> Database::exec(string query)
{
	QueryResponse<User> response;

	sqlite3* db = Database::open("cpp.db");
	int rc = sqlite3_exec(db, query.c_str(), callback, &response, nullptr);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_close(db);

	return response;
}

int Database::exec(string query, vector<string>& values)
{
	sqlite3* db = Database::open("cpp.db");
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		return rc;
	}
	for(int i = 0; i < values.size(); i++)
	{
		sqlite3_bind_text(stmt, i + 1, values[i].c_str(), -1, SQLITE_STATIC);
	}
	rc = sqlite3_step(stmt);
	if(rc != SQLITE_DONE)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		return rc;
	}
	sqlite3_finalize(stmt);

	sqlite3_close(db);
	return rc;
};

QueryResponse<User> Database::select(string query, vector<string>& values)
{
	QueryResponse<User> response;

	sqlite3* db = Database::open("cpp.db");

  build_query(query, values);

	int rc = sqlite3_exec(db, query.c_str(), callback, &response, nullptr);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_close(db);

	return response;
}

string Database::build_query(string& query, vector<string>& values) 
{ 
  while (query.find("?") != string::npos) 
  { 
    query.replace(query.find("?"), 1, '"' + values.front() + '"'); 
    values.erase(values.begin()); 
  } 
  return query;
}
