#include "num.h"

inline Num::Num(int value, int modulo) {
    this->modulo = modulo;
    this->value = value % modulo;
}

inline Num::Num(const Num& other) {
    this->value = other.value;
    this->modulo = 0;
}
