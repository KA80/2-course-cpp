#include "num.h"

inline Num::Num(int value, int modulo) {
    this->value = value % modulo;
    this->modulo = modulo;
}

inline Num& Num::operator=(const Num& other) {
    if (this == &other)
        return *this;
    value = other.value;
    modulo = other.modulo;
    return *this;
}

inline Num Num::operator+(const Num& other) {
    int value = (this->value + other.value) % modulo;
    return Num(value, modulo);
}


inline Num Num::operator-(const Num& other) {
    int value = (this->value - other.value) % modulo;
    return Num(value, modulo);
}


inline Num Num::operator*(const Num& other) {
    int value = (this->value * other.value) % modulo;
    return Num(value, modulo);
}


inline Num Num::operator+(int num) {
    int value = (this->value + num) % modulo;
    return Num(value, modulo);
}


inline Num Num::operator-(int num) {
    return operator+(-num);
}


inline Num Num::operator*(int num) {
    int value = (this->value * num) % modulo;
    return Num(value, modulo);
}


inline Num& Num::operator+=(const Num& other) {
    value = (value + other.value) % modulo;
    return *this;
}


inline Num& Num::operator-=(const Num& other) {
    if (value > other.value)
        value = (value - other.value) % modulo;
    else
        value = (value + modulo - other.value) % modulo;
    return *this;
}


inline Num& Num::operator*=(const Num& other) {
    value = (value * other.value) % modulo;
    return *this;
}


inline Num& Num::operator+=(int num) {
    if (num < 0)
        num = modulo + num;
    unsigned int remainder = num % modulo;
    value = (value + remainder) % modulo;
    return *this;
}


inline Num& Num::operator-=(int num) {
    return operator+=(-num);
}


inline Num& Num::operator*=(int num) {
    int a = num % modulo;
    unsigned int value = 0;                      //TODO
    for (int i = 0; i < a; i++) {                //Слишком долго
        value = (value + this->value) % modulo;  //надо переделать
    }
    this->value = value;

    return *this;
}