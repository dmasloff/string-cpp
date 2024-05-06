#ifndef // STRING_H
#define // STRING_H

#include <algorithm>
#include <cstring>
#include <iostream>

class String {
 public:
  String(size_t size, char symbol);
  String(const String& str);
  String(const char* ptr);
  String(char c);
  String(const String& str, size_t start, size_t cnt);
  String();
  ~String();

  String& operator=(String str);
  char& operator[](size_t size);
  const char& operator[](size_t size) const;

  size_t length() const;
  size_t size() const;
  size_t capacity() const;

  void push_back(char symbol);
  void pop_back();
  char& front();
  const char& front() const;
  char& back();
  const char& back() const;

  String& operator+=(char symbol);
  String& operator+=(const String& str);

  size_t find(const String& str) const;
  size_t rfind(const String& str) const;
  String substr(size_t start, size_t count) const;
  bool empty() const;
  void clear();
  void shrink_to_fit();
  char* data();
  const char* data() const;

 private:
  char* array = nullptr;
  size_t sz = 0;
  size_t cap = 0;

  void swap(String& str);
  void memoryredistribution(size_t length);
  String(const String& str, size_t length);
};

bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);
bool operator<(const String& a, const String& b);
bool operator>(const String& a, const String& b);
bool operator<=(const String& a, const String& b);
bool operator>=(const String& a, const String& b);
bool substring_comparison(const String& a, const String& b, size_t a_index,
                          size_t b_index, size_t length);
String operator+(const String& a, const String& b);
std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);

#endif // STRING_H