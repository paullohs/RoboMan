#include "Mat.hpp"
#include "Vec.hpp"

MAT::MAT() : aa(0), ab(0), ac(0), ba(0), bb(0), bc(0), ca(0), cb(0), cc(0) {
}

MAT::MAT(NUM _aa, NUM _ab, NUM _ac, NUM _ba, NUM _bb, NUM _bc, NUM _ca, NUM _cb, NUM _cc) :
  aa(_aa), ab(_ab), ac(_ac), ba(_ba), bb(_bb), bc(_bc), ca(_ca), cb(_cb), cc(_cc) {
}

MAT::MAT(MAT &b) : aa(b.aa), ab(b.ab), ac(b.ac), ba(b.ba), bb(b.bb), bc(b.bc), ca(b.ca), cb(b.cb), cc(b.cc) {
}

MAT::~MAT() {
}

MAT& MAT::operator=(MAT &b)
{
  aa = b.aa;
  ab = b.ab;
  ac = b.ac;
  ba = b.ba;
  bb = b.bb;
  bc = b.bc;
  ca = b.ca;
  cb = b.cb;
  cc = b.cc;
  return *this;
}

MAT MAT::operator*(NUM &b) {
  return MAT(aa*b, ab*b, ac*b,
             ba*b, bb*b, bc*b,
             ca*b, cb*b, cc*b);
}

MAT MAT::operator*(VEC &b) {
  return MAT(aa*b.a, ab*b.a, ac*b.a,
             ba*b.b, bb*b.b, bc*b.b,
             ca*b.c, cb*b.c, cc*b.c);
}

MAT MAT::operator*(MAT &b) {
  return MAT(aa*b.aa + ab*b.ba + ac*b.ca, aa*b.ab + ab*b.bb + ac*b.cb, aa*b.ac + ab*b.bc + ac*b.cc,
             ba*b.aa + bb*b.ba + bc*b.ca, ba*b.ab + bb*b.bb + bc*b.cb, ba*b.ac + bb*b.bc + bc*b.cc,
             ca*b.aa + cb*b.ba + cc*b.ca, ca*b.ab + cb*b.bb + cc*b.cb, ca*b.ac + cb*b.bc + cc*b.cc);
}

MAT MAT::operator+(MAT &b) {
  return MAT(aa + b.aa, ab + b.ab, ac + b.ac,
             ba + b.ba, bb + b.bb, bc + b.bc,
             ca + b.ca, cb + b.cb, cc + b.cc);
}

MAT MAT::operator-(MAT &b) {
  return MAT(aa - b.aa, ab - b.ab, ac - b.ac,
             ba - b.ba, bb - b.bb, bc - b.bc,
             ca - b.ca, cb - b.cb, cc - b.cc);
}