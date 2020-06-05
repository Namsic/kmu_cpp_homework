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
  return (*this) + myComplex(value);
}
myComplex operator +(int value, const myComplex& number){
  return myComplex(value) + number;
}
myComplex myComplex::operator -(const myComplex& number) const{
  int newReal = realPart - number.realPart;
  int newImag = imaginaryPart - number.imaginaryPart;
  return myComplex (newReal, newImag);
}
myComplex myComplex::operator -(int value) const{
  return (*this) - myComplex(value);
}
myComplex operator -(int value, const myComplex& number){
  return myComplex(value) - number;
}
myComplex myComplex::operator *(const myComplex& number) const{
  int newReal = realPart*number.realPart - imaginaryPart*number.imaginaryPart;
  int newImag = realPart*number.imaginaryPart + imaginaryPart*number.realPart;
  return myComplex (newReal, newImag);
}
myComplex myComplex::operator *(int value) const{
  return (*this) * myComplex(value);
}
myComplex operator *(int value, const myComplex& number){
  return myComplex(value) * number;
}

myComplex myComplex::operator +=(const myComplex& number){
  (*this) = (*this) + number;
  return *this;
}
myComplex myComplex::operator +=(int value){
  (*this) = (*this) + value;
  return *this;
}
myComplex operator +=(int value, myComplex& number){
  return value + number;
}
myComplex myComplex::operator -=(const myComplex& number){
  (*this) = (*this) - number;
  return *this;
}
myComplex myComplex::operator -=(int value){
  (*this) = (*this) - value;
  return *this;
}
myComplex operator -=(int value, myComplex& number){
  return value - number;
}
myComplex myComplex::operator *=(const myComplex& number){
  (*this) = (*this) * number;
  return *this;
}
myComplex myComplex::operator *=(int value){
  (*this) = (*this) * value;
  return *this;
}
myComplex operator *=(int value, myComplex& number){
  return value * number;
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
bool myComplex::operator !=(const myComplex& number) const{
  return (realPart != number.realPart) ||
    (imaginaryPart != number.imaginaryPart);
}
bool myComplex::operator >(const myComplex& number) const{
  return norm() > number.norm();
}
bool myComplex::operator >=(const myComplex& number) const{
  return norm() >= number.norm();
}
bool myComplex::operator <(const myComplex& number) const{
  return norm() < number.norm();
}
bool myComplex::operator <=(const myComplex& number) const{
  return norm() <= number.norm();
}

myComplex myComplex::operator -(){
  return myComplex(-realPart, -imaginaryPart);
}
myComplex myComplex::operator ~(){
  return myComplex(realPart, -imaginaryPart);
}
myComplex& myComplex::operator ++(){
  realPart++;
  return *this;
}
myComplex myComplex::operator ++(int){
  myComplex tmp(*this);
  ++(*this);
  return tmp;
}
myComplex& myComplex::operator --(){
  realPart--;
  return *this;
}
myComplex myComplex::operator --(int){
  myComplex tmp(*this);
  --(*this);
  return tmp;
}

int myComplex::norm() const{
  return realPart * realPart + imaginaryPart * imaginaryPart;
}

ostream &operator <<(ostream &outStream, const myComplex& number){
  outStream << "(" << number.realPart << "," <<
    number.imaginaryPart << ")";
  return outStream;
}

istream &operator >>(istream &inStream, myComplex& number){
  inStream >> number.realPart >> number.imaginaryPart;
  return inStream;
}
