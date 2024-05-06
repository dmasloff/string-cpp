#include "string.h"

String::String(size_t size, char symbol)
    : array(new char[size + 1]), sz(size), cap(size) {
  std::fill(array, array + size, symbol);
  array[sz] = '\0';
}

String::String(const String& str) : String(str.sz, '\0') {
  std::copy(str.array, str.array + str.sz, array);
}

String::String(const char* ptr) : String(strlen(ptr), '\0') {
  std::copy(ptr, ptr + strlen(ptr), array);
  array[sz] = '\0';
}

String::String(char c) : String(1, c) {
  array[sz] = '\0';
}

String::String(const String& str, size_t start, size_t cnt)
    : String((str.sz > start) ? std::min(str.sz - start, cnt) : 0, '\0') {
  if (sz > 0) {
    std::copy(str.array + start, str.array + start + sz, array);
  }
  array[sz] = '\0';
}

String::String(const String& str, size_t length)
    : array(new char[length + 1]), sz(str.sz), cap(length) {
  std::copy(str.array, str.array + str.sz, array);
  array[sz] = '\0';
}

String::String() : array(new char[1]), sz(0), cap(0) {
  array[0] = '\0';
}

String::~String() {
  delete[] array;
}

void String::swap(String& str) {
  std::swap(array, str.array);
  std::swap(sz, str.sz);
  std::swap(cap, str.cap);
}

void String::memoryredistribution(size_t length) {
  char* ptr = array;
  cap = length;
  sz = std::min(sz, cap);
  array = new char[cap + 1];
  std::copy(ptr, ptr + sz, array);
  delete[] ptr;
}

String& String::operator=(String str) {
  swap(str);
  return *this;
}

char& String::operator[](size_t size) {
  return array[size];
}

const char& String::operator[](size_t size) const {
  return array[size];
}

size_t String::length() const {
  return sz;
}

size_t String::size() const {
  return sz;
}

size_t String::capacity() const {
  return cap;
}

void String::push_back(char symbol) {
  if (sz == cap) {
    memoryredistribution(2 * cap + 1);
  }
  array[sz] = symbol;
  ++sz;
  array[sz] = '\0';
}

void String::pop_back() {
  --sz;
  array[sz] = '\0';
}

char& String::front() {
  return array[0];
}

const char& String::front() const {
  return array[0];
}

char& String::back() {
  return array[sz - 1];
}

const char& String::back() const {
  return array[sz - 1];
}

String& String::operator+=(char symbol) {
  push_back(symbol);
  return *this;
}

String& String::operator+=(const String& str) {
  if (sz + str.sz > cap) {
    memoryredistribution(2 * (sz + str.sz));
  }
  std::copy(str.array, str.array + str.sz, array + sz);
  sz += str.sz;
  array[sz] = '\0';
  return *this;
}

size_t String::find(const String& str) const {
  for (size_t i = 0; i + str.sz <= sz; ++i) {
    if (substring_comparison(*this, str, i, 0, str.size())) {
      return i;
    }
  }
  return sz;
}

size_t String::rfind(const String& str) const {
  if (sz < str.sz) {
    return sz;
  }
  for (size_t i = sz - str.sz; i > 0; --i) {
    if (substring_comparison(*this, str, i, 0, str.size())) {
      return i;
    }
  }
  if (array[0] == str.array[0]) {
    if (substring_comparison(*this, str, 0, 0, str.size())) {
      return 0;
    }
  }
  return sz;
}

String String::substr(size_t start, size_t count) const {
  return String(*this, start, count);
}

bool String::empty() const {
  return sz == 0;
}

void String::clear() {
  sz = 0;
  array[sz] = '\0';
}

void String::shrink_to_fit() {
  if (sz < cap) {
    memoryredistribution(sz);
  }
}

char* String::data() {
  return array;
}

const char* String::data() const {
  return array;
}

bool operator==(const String& a, const String& b) {
  if (a.size() != b.size()) {
    return false;
  }
  size_t i = 0;
  while (i < a.size() && a[i] == b[i]) {
    ++i;
  }
  return i == a.size();
}

bool operator!=(const String& a, const String& b) {
  return !(a == b);
}

bool operator<(const String& a, const String& b) {
  size_t i = 0, limit = std::min(a.size(), b.size());
  while (i < limit && a[i] == b[i]) {
    ++i;
  }
  if (i == limit) {
    return a.size() < b.size();
  }
  return a[i] < b[i];
}

bool operator>(const String& a, const String& b) {
  return b < a;
}

bool operator<=(const String& a, const String& b) {
  return !(a > b);
}

bool operator>=(const String& a, const String& b) {
  return b <= a;
}

bool substring_comparison(const String& a, const String& b, size_t a_index,
                          size_t b_index, size_t length) {
  size_t i = 0;
  while (a_index + i < a.size() && i < length &&
         a[a_index + i] == b[b_index + i]) {
    ++i;
  }
  return i == length;
}

String operator+(const String& a, const String& b) {
  String res = a;
  res += b;
  return res;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    os << str[i];
  }
  return os;
}

std::istream& operator>>(std::istream& is, String& str) {
  char tmp;
  str.clear();
  while (is.get(tmp)) {
    if (tmp == ' ' || tmp == '\n') {
      break;
    }
    str.push_back(tmp);
  }
  return is;
}