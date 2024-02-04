#ifndef QUERY_RESPONSE_H
#define QUERY_RESPONSE_H

#include <vector>
#include <crow/app.h>

template <typename T> class QueryResponse {
public:
  QueryResponse() : data({}), error(nullptr) {}
  void add_data(T d);

  std::vector<T> get_data() { return data; };
  std::vector<crow::json::wvalue> dto();

private:
  std::vector<T> data;
  char *error;
};

#endif
