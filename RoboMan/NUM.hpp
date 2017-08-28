#pragma once
#include <string>

class __declspec(dllexport) NUM {
  friend class MAT;
  friend class VEC;

public:
  NUM();
  NUM(double _a);
  NUM(NUM &b);
  ~NUM();

  NUM operator*(NUM &b);
  NUM operator+(NUM &b);
  NUM operator-(NUM &b);
  NUM operator/(NUM &b);

  int ToInt() { return static_cast<int>(a); }
  std::string ToString() { return std::to_string(a); }
  operator double() const { return a; }

private:
  double a;
};