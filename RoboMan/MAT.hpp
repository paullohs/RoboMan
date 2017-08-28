#pragma once
#include "Num.hpp"

class VEC;

class __declspec(dllexport) MAT {
public:
  MAT();
  MAT(NUM _aa, NUM _ab, NUM _ac, NUM _ba, NUM _bb, NUM _bc, NUM _ca, NUM _cb, NUM _cc);
  MAT(MAT &b);
  ~MAT();

  MAT& operator=(MAT &b);
  MAT operator*(VEC & b);
  MAT operator*(MAT & b);
  MAT operator*(NUM &b);
  MAT operator+(MAT &b);
  MAT operator-(MAT &b);

private:
  NUM aa, ab, ac;
  NUM ba, bb, bc;
  NUM ca, cb, cc;
};