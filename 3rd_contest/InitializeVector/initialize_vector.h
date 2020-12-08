#include <vector>

template<typename T, typename Last>
auto initialize_vector(T t, Last size) {
    return std::vector<T>(size, t);
}

template<typename T, typename First, typename ...Args>
auto initialize_vector(T t, First size, Args... args) {
  auto dim = initialize_vector(t, args...);
  return std::vector<decltype(dim)>(size, dim);
}
