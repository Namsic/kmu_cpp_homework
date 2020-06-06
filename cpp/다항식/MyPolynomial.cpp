#include "MyPolynomial.h"

myPolynomial::myPolynomial(int c, unsigned int e){
  terms[0] = myTerm(c, e);
}
myPolynomial::myPolynomial(int nTerms, int mono[]){
  for(int i=0; i<nTerms; i++){
    int c = mono[i*2];
    int e = mono[i*2+1];
    insertTerm(c, e);
  }
}

// copy constructor
myPolynomial::myPolynomial(const myPolynomial &poly){
  for(int i=0; i<50; i++)
    terms[i] = myTerm(poly.terms[i]);
}

// overloaded operators
bool myPolynomial::operator == (const myPolynomial &poly) const{
  for(int i=0; i<50; i++)
    if(terms[i] != poly.terms[i])
      return false;
  return true;
}
bool myPolynomial::operator != (const myPolynomial &poly) const{
  return !((*this) == poly);
}
myPolynomial& myPolynomial::operator += (const myPolynomial &poly){
  (*this) = (*this) + poly;
  return *this;
}
myPolynomial& myPolynomial::operator -= (const myPolynomial &poly){
  (*this) = (*this) - poly;
  return *this;
}
myPolynomial& myPolynomial::operator *= (const myPolynomial &poly){
  (*this) = (*this) * poly;
  return *this;
}
myPolynomial& myPolynomial::operator *= (int k){
  (*this) = (*this) * k;
  return *this;
}
myPolynomial myPolynomial::operator -() const{
  myPolynomial temp(*this);
  for(int i=0; i<getNumTerms(); i++){
    temp.terms[i] = -temp.terms[i];
  }
  return temp;
}
myPolynomial myPolynomial::operator *(int k) const{
  myPolynomial temp;
  for(int i=0; i<getNumTerms(); i++)
    temp.terms[i] = myTerm(terms[i].getCoeff() * k, terms[i].getExp());
  temp.pullTerms();
  return temp;
}
myPolynomial myPolynomial::operator +(const myPolynomial &poly) const{
  myPolynomial temp(*this);
  //myTerm(temp.terms[i].getCoeff() + poly.terms[i].getCoeff(), i);
  for(int i=0; i<poly.getNumTerms(); i++){
    int j;
    for(j=0; j<50; j++)
      if(temp.terms[j].getExp() == poly.terms[i].getExp()){
        int c = temp.terms[j].getCoeff() + poly.terms[i].getCoeff();
        int e = temp.terms[j].getExp();
        temp.terms[j] = myTerm(c, e);
        break;
      }
    if(j == 50){
      int c = poly.terms[i].getCoeff();
      int e = poly.terms[i].getExp();
      temp.insertTerm(c, e);
    }
  }
  temp.pullTerms();
  return temp;
}
myPolynomial myPolynomial::operator -(const myPolynomial &poly) const{
  return (*this) + (-poly);
}
myPolynomial myPolynomial::operator *(const myPolynomial &poly) const{
  myPolynomial temp;
  for(int i=0; i<getNumTerms(); i++)
    for(int j=0; j<poly.getNumTerms(); j++){
      int c = terms[i].getCoeff() * poly.terms[j].getCoeff();
      int e = terms[i].getExp() + poly.terms[j].getExp();
      int k;
      for(k=0; k<temp.getNumTerms(); k++)
        if(temp.terms[k].getExp() == e){
          temp.terms[k] = myTerm(temp.terms[k].getCoeff() + c, e);
          break;
        }
      if(k == temp.getNumTerms())
        temp.insertTerm(c, e);
    }
  return temp;
}
long myPolynomial::operator() (int x) const{
  long res = 0;
  for(int i=0; i<getNumTerms(); i++){
    int p = 1;
    for(int j=0; j<terms[i].getExp(); j++)
      p *= x;
    res += p * terms[i].getCoeff();
  }
  return res;
}

int myPolynomial::getDegree() const{
  //if((*this) == myPolynomial::ZERO)
  //  return -1;
  //return terms[0].getExp();
}
unsigned myPolynomial::getNumTerms() const{
  int i = 0;
  while(i < 50 && terms[i].getCoeff() != 0)
    i++;
  return i;
}
myPolynomial myPolynomial::ddx() const{
  myPolynomial temp;
  for(int i=0; i<getNumTerms(); i++){
    temp.terms[i] = terms[i].ddx();
  }
  return temp;
}

void myPolynomial::pullTerms(){
  for(int i=0; i<50; i++){
    if(terms[i] == myTerm(0))
      break;
    while(terms[i].getCoeff() == 0){
      if(terms[i] == myTerm(0))
        break;
      for(int j=i; j<49; j++)
        terms[j] = myTerm(terms[j+1]);
      terms[49] = myTerm(0);
    }
  }

}
void myPolynomial::insertTerm(int c, unsigned e){
  myTerm temp(c, e);
  if(e == 0)
    for(int i=0; i<50; i++)
      if(terms[i] == myTerm(0)){
        terms[i] = myTerm(c, e);
        return;
      }
  int i = 49;
  while(i > 0 && temp < terms[i-1]){
    terms[i] = terms[i-1];
    i--;
  }
  terms[i] = temp;
}

// friend operators and functions
myPolynomial operator *(int k, const myPolynomial &poly){
  return poly * k;
}

// output operator
ostream& operator <<(ostream &outStream, const myPolynomial& poly){
  if(poly == myPolynomial::ZERO){
    return outStream << 0;
  }
  for(int i=0; i<poly.getNumTerms(); i++){
    if(i != 0 && poly.terms[i].getCoeff() > 0)
      outStream << "+";
    outStream << poly.terms[i];
  }
  return outStream;
}

const myPolynomial myPolynomial::ZERO(0); // the zero polynomial P(x) = 0
const myPolynomial myPolynomial::ONE(1, (unsigned)0); // the monomial P(x) = 1
const myPolynomial myPolynomial::X(1, 1); // the monomial P(x) = x
