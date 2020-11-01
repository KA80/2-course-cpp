#include <iostream>
#include <memory>
#include <cstdint>
#include <map>
#include <iterator>

template<typename Tp>
class FixedAllocator {
  PageAllocator page_allocator_;
  std::map<Tp *, int64_t> pool_fr_ptrs;
  uint64_t page_size;
  uint64_t sum = 0;
  void *last_ptr;

 public:
  explicit FixedAllocator(std::uint64_t page_size) : page_allocator_(
      page_size * sizeof(Tp)), page_size(page_size * sizeof(Tp)) {}

  Tp *Allocate() {
    if (!pool_fr_ptrs.empty()) {
      auto b = (--pool_fr_ptrs.end())->first;
      (--pool_fr_ptrs.end())->second -= 1;
      if ((--pool_fr_ptrs.end())->second == 0) {
        pool_fr_ptrs.erase(--pool_fr_ptrs.end());
      }
      return b;
    }
    if (sum == page_size) {
      sum = 0;
    }
    if (sum == 0) {
      void *r_pointer = page_allocator_.Allocate();
      last_ptr = r_pointer;
      sum += sizeof(Tp);
      return reinterpret_cast<Tp *>(r_pointer);
    }
    sum += sizeof(Tp);
    return reinterpret_cast<Tp *>(last_ptr);
  }

  void Deallocate(Tp *p) {
    pool_fr_ptrs[p] += 1;
  }

  const PageAllocator &InnerAllocator() const noexcept {
    return page_allocator_;
  }
};
