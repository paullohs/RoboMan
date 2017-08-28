#include "Num.hpp"

NUM::NUM() : a(0) {
}

NUM::NUM(double _a) : a(_a) {
}

NUM::NUM(NUM &b) : a(b.a) {
}

NUM::~NUM() {
}

NUM NUM::operator*(NUM &b) {
  return this->a * b.a;
}

NUM NUM::operator+(NUM &b) {
  return this->a + b.a;
}

NUM NUM::operator-(NUM &b) {
  return this->a - b.a;
}

NUM NUM::operator/(NUM &b) {
  return this->a / b.a;
}