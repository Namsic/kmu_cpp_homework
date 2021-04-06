#ifndef _MYCOMPLEX_H_
#define _MYCOMPLEX_H_
#include <iostream>
using namespace std;

class myComplex {
public:
  myComplex(int real = 0, int imag = 0);
  myComplex(const myComplex&);

  int getRealPart() const;
  int getImaginaryPart() const;

  void setRealPart(int);
  void setImaginaryPart(int);
  void set(int, int);

  myComplex operator +(const myComplex&) const;
  myComplex operator +(int) const;
  friend myComplex operator +(int, const myComplex&);
  myComplex operator -(const myComplex&) const;
  myComplex operator -(int) const;
  friend myComplex operator -(int, const myComplex&);
  myComplex operator *(const myComplex&) const;
  myComplex operator *(int) const;
  friend myComplex operator *(int, const myComplex&);

  myComplex operator +=(const myComplex&);
  myComplex operator +=(int);
  myComplex operator -=(const myComplex&);
  myComplex operator -=(int);
  myComplex operator *=(const myComplex&);
  myComplex operator *=(int);

  myComplex& operator =(const myComplex&);
  myComplex& operator =(int);

  bool operator ==(const myComplex&) const;
  bool operator !=(const myComplex&) const;
  bool operator >(const myComplex&) const;
  bool operator >=(const myComplex&) const;
  bool operator <(const myComplex&) const;
  bool operator <=(const myComplex&) const;

  myComplex operator -();
  myComplex operator ~();
  myComplex& operator ++();
  myComplex operator ++(int);
  myComplex& operator --();
  myComplex operator --(int);

  friend ostream &operator <<(ostream&, const myComplex&);
  friend istream &operator >>(istream&, myComplex&);

private:
  int realPart;
  int imaginaryPart;
  int norm() const;
};

myComplex operator +(int, const myComplex&);
myComplex operator -(int, const myComplex&);
myComplex operator *(int, const myComplex&);
myComplex operator +=(int, myComplex&);
myComplex operator -=(int, myComplex&);
myComplex operator *=(int, myComplex&);

ostream &operator <<(ostream&, const myComplex&);
istream &operator >>(istream&, myComplex&);

#endif
