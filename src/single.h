/*
    Single Indirection

    Naive implementation. Each strong ptr
    stores a ref to its counts and the
    allocated resource.

    Thus to access the underlying resource,
    only one layer of indirection is needed.
*/

#pragma once

#include <cstdint>

namespace impl {
template <typename T> class Single {
private:
  // not an ARC
  uint32_t *count;
  T *ptr;

  void point_away() {
    if (--(*count) == 0) {
      if (ptr != nullptr)
        delete ptr;
      delete count; // bc last one
    }
  }

public:
  Single() {
    count = new uint32_t(1);
    ptr = nullptr;
  }

  ~Single() { point_away(); }

  Single(const Single<T> &src) {
    (*src.count)++;
    count = src.count;
    ptr = src.ptr;
  }

  Single(T *p) {
    count = new uint32_t(1);
    ptr = p;
  }

  Single<T> &operator=(const Single<T> &rhs) {
    (*rhs.count)++;
    point_away();
    count = rhs.count;
    ptr = rhs.ptr;

    return *this;
  }

  Single<T> &operator=(T *p) {
    point_away();
    count = new uint32_t(1);
    ptr = p;

    return *this;
  }

  T *operator->() { return ptr; }
};
} // namespace impl
