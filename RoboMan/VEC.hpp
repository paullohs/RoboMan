#pragma once
#include "Num.hpp"

class __declspec(dllexport) VEC {
  friend class MAT;
  friend class NUM;

public:
  VEC();
  VEC(NUM _a, NUM _b, NUM _c);
  VEC(VEC &b);
  ~VEC();

  VEC operator*(VEC &b);
  VEC operator+(VEC &b);
  VEC operator-(VEC &b);
  NUM a, b, c;

private:
};