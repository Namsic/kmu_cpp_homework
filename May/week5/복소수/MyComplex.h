#ifndef _MYCOMPLEX_H_
#define _MYCOMPLEX_H_
#include <iostream>
using namespace std;

class myComplex {
public:
  myComplex(int real = 0, int imag = 0);
  myComplex(const myComplex& number);

  int getRealPart() const;
  int getImaginaryPart() const;

  void setRealPart(int real);
  void setImaginaryPart(int imag);
  void set(int real, int imag);

  myComplex operator +(const myComplex& number) const;
  myComplex operator +(int value) const;

  myComplex& operator =(const myComplex& number);
  myComplex& operator =(int value);

  bool operator ==(const myComplex& number) const;

  myComplex operator -(); // unary minus

private:
  int realPart;
  int imaginaryPart;
  int norm() const;
};

#endif
