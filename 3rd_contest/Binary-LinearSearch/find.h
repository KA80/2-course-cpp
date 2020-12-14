#include <iterator>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <list>

template<typename T, typename Iterator>
Iterator Find(const T &v,
              Iterator f,
              Iterator l,
              std::bidirectional_iterator_tag) {
  for (auto i = f; i != l; i++) {
    if (*i == v) {
      return i;
    }
  }
  return l;
}

template<typename T, typename Iterator>
Iterator Find(const T &v,
              Iterator f,
              Iterator l,
              std::random_access_iterator_tag) {
  Iterator last = l;
  Iterator mid;
  while (f < l) {
    int dif = (l - f) / 2;
    mid = f + dif;

    if (*mid < v) {
      f = mid + 1;
    } else {
      l = mid;
    }
  }
  return *f == v ? f : last;
}

template<typename T, typename Iterator>
Iterator Find(const T &value, Iterator first, Iterator last) {
  return Find(value,
              first,
              last,
              typename std::iterator_traits<Iterator>::iterator_category());
}
