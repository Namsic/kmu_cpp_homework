#include "MyHammingDistance.h"

#define XOR(a,b) (!(a)^!(b))

// constructors
MyBinaryNumber::MyBinaryNumber()
:value(0)
{
}
MyBinaryNumber::MyBinaryNumber(unsigned int val)
:value(val)
{
}

// accessor functions
unsigned int MyBinaryNumber::getValue() const{
    return value;
}

// mutator functions
void MyBinaryNumber::setValue(unsigned int val){
    value = val;
}

int MyBinaryNumber::getHammingWeight() const{
    int cnt = 0;
    unsigned int v = value;
    while(v > 0){
        cnt += v%2;
        v >>= 1;
    }
    return cnt;
}

// compute Hamming Distance
int MyBinaryNumber::getHammingDistance(const MyBinaryNumber& bn) const{
    int cnt = 0;
    unsigned int v = ~value ^ ~bn.getValue();
    while(v > 0){
        cnt += v%2;
        v >>= 1;
    }
    return cnt;
}
