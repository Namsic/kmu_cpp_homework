#include "MyComplex.h"

myComplex::myComplex(int real, int imag){
realPart = real;
imaginaryPart = imag;
}
myComplex::myComplex(const myComplex& number){
realPart = number.realPart;
imaginaryPart = number.imaginaryPart;
}

int myComplex::getRealPart() const{ return realPart; }
int myComplex::getImaginaryPart() const{ return imaginaryPart; }

void myComplex::setRealPart(int real){ realPart = real; }
void myComplex::setImaginaryPart(int imag) { imaginaryPart = imag; }
void myComplex::set(int real, int imag){
  realPart = real;
  imaginaryPart = imag;
}

myComplex myComplex::operator +(const myComplex& number) const{
  int newReal = realPart + number.realPart;
  int newImag = imaginaryPart + number.imaginaryPart;
  return myComplex (newReal, newImag);
}
myComplex myComplex::operator +(int value) const{
  return myComplex(value) + (*this);
}

myComplex& myComplex::operator =(const myComplex& number){
  this->realPart = number.realPart;
  this->imaginaryPart = number.imaginaryPart;
  return *this;
}

myComplex& myComplex::operator =(int value){
  realPart = value;
  imaginaryPart = 0;
  return *this;
}

bool myComplex::operator ==(const myComplex& number) const{
  return (realPart == number.realPart) &&
    (imaginaryPart == number.imaginaryPart);
}
bool myComplex::operator >(const myComplex& number) const{
  return norm() > number.norm();
}

myComplex myComplex::operator -(){
  return myComplex(-realPart, -imaginaryPart);
}

int myComplex::norm() const{
  return realPart * realPart + imaginaryPart * imaginaryPart;
}

ostream &operator <<(ostream &outStream, const myComplex& number){
  outStream << "(" << number.realPart << "," << number.imaginaryPart << ")";
  return outStream;
}

istream &operator >>(istream &inStream, myComplex& number){
  inStream >> number.realPart >> number.imaginaryPart;
  return inStream;
}
