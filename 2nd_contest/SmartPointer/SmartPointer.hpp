#pragma once

#include <memory>
#include <typeinfo>
#include <utility>
#include "Test.hpp"

namespace smart_pointer {
// `exception` class definition
class exception : std::exception {
  using base_class = std::exception;
  using base_class::base_class;
};

// `SmartPointer` class declaration
template<
    typename T,
    typename Allocator
>
class SmartPointer {
  // don't remove this macro
  ENABLE_CLASS_TESTS;

 public:
  using value_type = T;

  explicit SmartPointer(value_type *obj = nullptr) {
    if (obj == nullptr) {
      core = nullptr;
    } else {
      core = new Core(obj);
    }
  }

  // copy constructor
  SmartPointer(const SmartPointer &other) {
    core = other.core;
    if (this->operator bool()) {
      core->SetCnt(core->GetCnt() + 1);
    }
  }

  // move constructor
  SmartPointer(SmartPointer &&other)  noexcept {
    core = std::move(other.core);
    other.core = nullptr;
  }

  // copy assigment
  SmartPointer &operator=(const SmartPointer &other) {
    this->~SmartPointer();
    core = other.core;
    if (this->operator bool()) {
      core->SetCnt(core->GetCnt() + 1);
    }
    return *this;
  }

  // move assigment
  SmartPointer &operator=(SmartPointer &&other)  noexcept {
    this->~SmartPointer();
    core = std::move(other.core);
    other.core = nullptr;
    return *this;
  }

  //
  SmartPointer &operator=(value_type *obj) {
    if (obj == nullptr) {
      delete core;
      core = nullptr;
    } else {
      if (operator bool()) {
        core->SetCnt(core->GetCnt() - 1);
        if (core->GetCnt() == 0) {
          delete core;
        }
      } else {
        delete core;
      }
      core = new Core(obj);
    }
    return *this;
  }

  ~SmartPointer() {
    if (operator bool()) {
      core->SetCnt(core->GetCnt() - 1);
      if (core->GetCnt() == 0) {
        delete core;
      }
    } else {
      delete core;
    }
  }

  // return reference to the object of class/type T
  // if SmartPointer contains nullptr throw `SmartPointer::exception`
  value_type &operator*() {
    if (!operator bool()) {
      throw smart_pointer::exception();
    }
    return *core->GetObj();
  }

  const value_type &operator*() const {
    if (!operator bool()) {
      throw smart_pointer::exception();
    }
    return *core->GetObj();
  }

  // return pointer to the object of class/type T
  value_type *operator->() const {
    return operator bool() ? core->GetObj() : nullptr;
  }

  value_type *get() const {
    return operator bool() ? core->GetObj() : nullptr;
  }

  // if pointer == nullptr => return false
  explicit operator bool() const {
    return core != nullptr;
  }

  // if pointers points to the same address or both null => true
  template<typename U, typename AnotherAllocator>
  bool operator==(const SmartPointer<U, AnotherAllocator> &other) const {
    if (typeid(U) != typeid(T)
        && ((get() == nullptr && other.get() != nullptr))) {
      return false;
    }
    if ((get() == nullptr && other.get() == nullptr)
        || reinterpret_cast<void *>(get())
            == reinterpret_cast<void *>(other.get())) {
      return true;
    }
    return false;
  }

  // if pointers points to the same address or both null => false
  template<typename U, typename AnotherAllocator>
  bool operator!=(const SmartPointer<U, AnotherAllocator> &other) const {
    return !(*this == other);
  }

  // if smart pointer contains non-nullptr => return count owners
  // if smart pointer contains nullptr => return 0
  std::size_t count_owners() const {
    return operator bool() ? core->GetCnt() : 0;
  }

 private:
  class Core {
    int64_t cnt = 1;
    value_type *obj;

   public:
    explicit Core(value_type *obj) : obj(obj) {}

    ~Core() {
      delete obj;
    }

    int64_t GetCnt() {
      return cnt;
    }

    void SetCnt(int64_t num) {
      cnt = num;
    }

    value_type *GetObj() {
      return obj;
    }
  };

  Core *core;
};
}  // namespace smart_pointer
