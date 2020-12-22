#include <string>
#include <thread>

void start_multithreading(std::string* str, int x) {
  for (; x < str->size(); x += 4) {
    (*str)[x] = 'a' + ((*str)[x] + 3 - 'a') % 26;
  }
}

void CaesarEncrypt(std::string* s) {
  std::thread threads[4] {
    std::thread(start_multithreading, s, 0),
    std::thread(start_multithreading, s, 1),
    std::thread(start_multithreading, s, 2),
    std::thread(start_multithreading, s, 3),
  };
  for (auto & thread : threads) {
    thread.join();
  }
}

