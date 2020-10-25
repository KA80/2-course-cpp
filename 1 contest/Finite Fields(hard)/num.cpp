#include "num.h"
#include <cmath>
#include <cstdint>

inline Num::Num(int value, int modulo) {
  this->value = value % modulo;
  this->modulo = modulo;
}

inline Num &Num::operator=(const Num &other) {
  if (this == &other)
    return *this;
  value = other.value;
  modulo = other.modulo;
  return *this;
}

inline Num Num::operator+(const Num &other) {
  int value = (this->value + other.value) % modulo;
  return Num(value, modulo);
}

inline Num Num::operator-(const Num &other) {
  int value = (this->value - other.value) % modulo;
  return Num(value, modulo);
}

inline Num Num::operator*(const Num &other) {
  int value = (this->value * other.value) % modulo;
  return Num(value, modulo);
}

inline Num Num::operator+(int num) {
  int value = (this->value + num) % modulo;
  return Num(value, modulo);
}

inline Num Num::operator-(int num) {
  int value = abs((this->value - num) % modulo);
  return Num(value, modulo);
}

inline Num Num::operator*(int num) {
  int value = (this->value * num) % modulo;
  return Num(value, modulo);
}

inline Num &Num::operator+=(const Num &other) {
  value = (value + other.value) % modulo;
  return *this;
}

inline Num &Num::operator-=(const Num &other) {
  if (value > other.value)
    value = (value - other.value) % modulo;
  else
    value = (value + modulo - other.value) % modulo;
  return *this;
}

inline Num &Num::operator*=(const Num &other) {
  value = (value * other.value) % modulo;
  return *this;
}

inline Num &Num::operator+=(int num) {
  int64_t value = this->value;
  value += num;
  value = value % this->modulo;
  this->value = value;

  return *this;
}

inline Num &Num::operator-=(int num) {
  if (value > num)
    value = (value - num) % modulo;
  else
    value = (value + modulo - num) % modulo;
  return *this;
}

inline Num &Num::operator*=(int num) {
  int64_t value = this->value;

  value *= num;
  value = value % this->modulo;

  this->value = value;
  return *this;
}
