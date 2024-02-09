#include "Result.h"
#include <crow/json.h>

Result::Result(int code, std::string message)
	: json({{"code", code}, {"message", message}})
{ }

Result::Result(int code, const crow::json::wvalue& data)
	: json({{"code", code}, {"data", data}})
{ }

Result Result::ok(int code)
{
  std::string message = "OK";
	Result result(code, message);
  return result;
}

Result Result::error(int code, std::string message) 
{
  Result result(code, message);
  return result;
}

Result Result::success(int code, const crow::json::wvalue& data)
{
  Result result(200, data);
  return result;
}

crow::json::wvalue Result::get_json()
{
	return this->json;
}
