#include <iostream>
#include <string>
#include <cmath>

class Date {
  int year, month, day;

  static int FindJulianDay(const Date &date) {  // Метод, возвращающий
    // дату по Юлиансому календарю
    int a = floor((14 - date.month) / 12);
    int y = date.year + 4800 - a;
    int m = date.month + 12 * a - 3;
    return date.day + floor((153 * m + 2) / 5) + 365 * y
        + floor(y / 4) - floor(y / 100)
        + floor(y / 400) - 32045;
  }

  static std::string ValueToString(int value, bool is_year) {
    unsigned int a = is_year ? 4 : 2;
    std::string str = std::to_string(value);
    while (str.size() < a)
      str = '0' + str;
    return str;
  }

 public:
  Date(int year, int month, int day) {
    this->day = day;
    this->month = month;
    this->year = year;
  }

  bool IsLeap() const {  // Метод, возвращающий true в случае,
    // если год является високосным и false в противном случае
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
      return true;
    return false;
  }

  std::string ToString() const {  // Метод, возвращающий строковое
    // представление даты в формате dd.mm.yyyy.
    return ValueToString(day, false) + '.'
        + ValueToString(month, false) + '.'
        + ValueToString(year, true);
  }

  Date DaysLater(int days) const {  // Метод, возвращающий дату,
    // которая наступит спустя days дней от текущей.
    int JD = FindJulianDay(*this) + days;

    // конвертер из Юлианской даты в Григорианскую
    // https://en.wikipedia.org/wiki/Julian_day

    int f = JD + 1401 + (((4 * JD + 274277) / 146097) * 3) / 4 - 38;
    int e = 4 * f + 3;
    int g = (e % 1461) / 4;
    int h = 5 * g + 2;

    int day = (h % 153) / 5 + 1;
    int month = (h / 153 + 2) % 12 + 1;
    int year = e / 1461 - 4716 + (14 - month) / 12;

    return Date(year, month, day);
  }

  int DaysLeft(const Date &date) const {  // Метод, возвращающий разницу
    // между указанной и текущей датой (в днях).
    int a = FindJulianDay(*this);
    int b = FindJulianDay(date);
    return b - a;
  }
};
