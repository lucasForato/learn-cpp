#ifndef QUERY_RESPONSE_H
#define QUERY_RESPONSE_H

#include <vector>

template <typename T> class QueryResponse {
public:
  QueryResponse() : data({}), error(nullptr) {}
  void add_data(T d);

private:
  std::vector<T> data;
  char *error;
};

#endif
