#include <cstdint>
#include <vector>
#include <utility>
#include <mutex>

template<typename T>
class Queue {
  std::vector<T> data;
  mutable std::mutex mutex_;

 public:
  T Pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    auto res = std::move(data[0]);
    data.erase(data.begin());
    return res;
  }

  size_t Size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return data.size();
  }

  template<typename U>
  void Push(U arg) {
    std::lock_guard<std::mutex> lock(mutex_);
    data.push_back(std::move(arg));
  }

  template<typename ... U>
  void Emplace(U&& ...args) {
    std::lock_guard<std::mutex> lock(mutex_);
    data.emplace_back(args...);
  }
};
