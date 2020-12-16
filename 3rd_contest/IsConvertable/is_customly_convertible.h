template<typename T1, typename T2>
struct is_customly_convertible {
  template<typename T3, typename T4>
  static char test(decltype(&Convert<T3, T4>::operator()));

  template<typename, typename>
  static int test(...);

 public:
  enum {
    value = std::is_same<decltype(test<T1, T2>(0)), char>::value
  };
};

struct NoTriviallyConstructible {
 public:
  NoTriviallyConstructible() = delete;
  explicit NoTriviallyConstructible(int) {}
  int value = 1;
};

struct NoCopyConstructible {
 public:
  NoCopyConstructible(const NoCopyConstructible &) = delete;
  void operator=(const NoCopyConstructible &) = delete;
  NoCopyConstructible() = default;
  int value = 0;
};

template< >
struct Convert<NoTriviallyConstructible, int> {
  int operator()(const NoTriviallyConstructible &trivial) {
    return trivial.value;
  }
};

template< >
struct Convert<NoCopyConstructible, NoTriviallyConstructible> {
  NoTriviallyConstructible operator()(const NoTriviallyConstructible &trivial) {
    return NoTriviallyConstructible(trivial.value);
  }
};
