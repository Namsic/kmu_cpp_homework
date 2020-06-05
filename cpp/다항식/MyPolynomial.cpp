#include "MyPolynomial.h"

/********************* add your code here ********************************/

// output operator
ostream& operator <<(ostream &outStream, const myPolynomial& poly){
  if (poly == myPolynomial::ZERO)
    return outStream << 0;

/********************* add your code here ********************************/
return outStream;
}

const myPolynomial myPolynomial::ZERO(0); // the zero polynomial P(x) = 0
const myPolynomial myPolynomial::ONE(1, (unsigned)0); // the monomial P(x) = 1
const myPolynomial myPolynomial::X(1, 1); // the monomial P(x) = x
