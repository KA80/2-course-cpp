#include <thread>

using M = DenseMat;
void start_multithreading(int t_cnt,
                          const M &a,
                          const M &b,
                          M *res,
                          int x) {
  for (; x < res->Rows() * res->Cols(); x += t_cnt) {
    auto r = x % res->Rows();
    auto c = x / res->Cols();
    for (int i = 0; i < a.Cols(); i++) {
      (*res)(r, c) += a(r, i) * b(i, c);
    }
  }
}

M MatMulParal(const M &a, const M &b, int thread_count) {
  M result = {a.Rows(), b.Cols()};
  std::thread threads[thread_count];
  for (int i = 0; i < thread_count; i++) {
    threads[i] =
        std::thread(start_multithreading, thread_count, a, b, &result, i);
  }
  for (auto &thread : threads) {
    thread.join();
  }
  return result;
}