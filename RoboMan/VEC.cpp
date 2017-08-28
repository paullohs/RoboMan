#include "Vec.hpp"

VEC::VEC() : a(0), b(0), c(0) {
}

VEC::VEC(NUM _a, NUM _b, NUM _c) : a(_a), b(_b), c(_c) {
}

VEC::VEC(VEC &b) : a(b.a), b(b.b), c(b.c) {
}

VEC::~VEC() {
}

VEC VEC::operator*(VEC &_b) {
  return VEC(a*_b.a, b*_b.b, c*_b.c);
}

VEC VEC::operator+(VEC &_b) {
  return VEC(a + _b.a, b + _b.b, c + _b.c);
}

VEC VEC::operator-(VEC &_b) {
  return VEC(a - _b.a, b - _b.b, c - _b.c);
}