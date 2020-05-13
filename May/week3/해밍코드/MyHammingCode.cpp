#include "MyHammingCode.h"

// constructors
MyHammingCode::MyHammingCode()
:value(0)
{
}

MyHammingCode::MyHammingCode(unsigned int val)
:value(val)
{
}

// utility functions
unsigned int MyHammingCode::getEncodedValue(){
    encodedValue = 0;

    encodedValue |= copyBits(value, 0, 1, 2);
    encodedValue |= copyBits(value, 1, 3, 4);
    encodedValue |= copyBits(value, 4, 7, 8);
    encodedValue |= copyBits(value, 11, 15, 16);

    encodedValue = setParityBit(encodedValue, 1);
    encodedValue = setParityBit(encodedValue, 2);
    encodedValue = setParityBit(encodedValue, 4);
    encodedValue = setParityBit(encodedValue, 8);
    encodedValue = setParityBit(encodedValue, 16);

    return encodedValue;
}

unsigned int MyHammingCode::getDecodedValue(){
    int errorPos;

    decodedValue = 0;

    errorPos = checkParityBit(value);
    if(errorPos > 0)
        value = negateBit(value, errorPos-1);

    decodedValue |= copyBits(value, 2, 1, 0);
    decodedValue |= copyBits(value, 4, 3, 1);
    decodedValue |= copyBits(value, 8, 7, 4);
    decodedValue |= copyBits(value, 16, 15, 11);

    return decodedValue;
}

unsigned int MyHammingCode::copyBits(unsigned int n, int from, int num, int to){
    unsigned int mask = 0;
    unsigned int code = 0;

    do{
        mask <<= 1;
        mask |= 0x01;
    }while(--num);

    n >>= from;
    n &= mask;
    code |= n;
    code <<= to;

    return code;
}

unsigned int MyHammingCode::setParityBit(unsigned int n, int pos){
    unsigned int mask[5] = {0x55555554, 0x66666664, 0x78787870, 
                            0x7F807F00, 0x7FFF0000};
    int count;
    unsigned int checkBits;

    switch(pos){
    case 1:
        checkBits = n & mask[0];
        break;
    case 2:
        checkBits = n & mask[1];
        break;
    case 4:
        checkBits = n & mask[2];
        break;
    case 8:
        checkBits = n & mask[3];
        break;
    case 16:
        checkBits = n & mask[4];
        break;
    }

    count = hammingWeight(checkBits);
    if(count % 2)
        n = setBit(n, pos-1);

    return n;
}

unsigned int MyHammingCode::checkParityBit(unsigned int n){
    int parity[5] = {0, 0, 0, 0, 0};
    unsigned int pos = 1;
    unsigned int errorPos = 0;
    int errorCnt = 0;

    for(int i=0; i<5; i++){ // pos == 2^i
        for(int p=pos-1; p<32; p+=pos*2)
            for(int j=0; j<pos; j++)
                parity[i] += checkBit(n, p+j);
        pos <<= 1;
    }

    pos = 1;
    for(int i=0; i<5; i++){
        if(parity[i]%2 != 0){
            errorPos += pos;
            errorCnt++;
        }
        pos <<= 1;
    }

    if(errorCnt > 1)
        return errorPos;
    else
        return 0;
}

int MyHammingCode::hammingWeight(unsigned int n){
    int cnt = 0;
    while(n > 0){
        cnt += n%2;
        n >>= 1;
    }
    return cnt;
}

unsigned int MyHammingCode::setBit(unsigned int n, int pos){
    unsigned int p = 1 << pos;
    return n | p;
}

unsigned int MyHammingCode::clearBit(unsigned int n, int pos){
    unsigned int p = 1 << pos;
    return n & ~p;
}

int MyHammingCode::checkBit(unsigned int n, int pos){
    return (n >> pos)%2;
}

unsigned int MyHammingCode::negateBit(unsigned int n, int pos){
    unsigned int p = 1 << pos;
    return _xor(n, p);
}

unsigned int MyHammingCode::_xor(unsigned int x, unsigned int y){
    return ~x ^ ~y;
}
