#ifndef RESULT_H
#define RESULT_H

#include <crow/json.h>
#include <string>

class Result
{
public:
	Result(int code, const crow::json::wvalue& data);
  Result(int code, std::string message);

	crow::json::wvalue get_json();
	static Result ok(int code = 200);
	static Result error(int code, std::string message);
	static Result success(int code, const crow::json::wvalue& data);

private:
	const crow::json::wvalue json;
};

#endif
