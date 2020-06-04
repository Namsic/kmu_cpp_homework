#include <iostream>
#include "MyIpv4Address.h"
using namespace std;

MyIpv4Address::MyIpv4Address()
:addNumber(0){
    num2address();
}

MyIpv4Address::MyIpv4Address(unsigned int num)
:addNumber(num){
    num2address();
}

MyIpv4Address::MyIpv4Address(char add[])
:addNumber(0){
    string2address(add);
    address2num();
}

void MyIpv4Address::printAddress() const{
    cout << (int)address[3] << ".";
    cout << (int)address[2] << ".";
    cout << (int)address[1] << ".";
    cout << (int)address[0] << endl;
}

void MyIpv4Address::printNumber() const{
    cout << addNumber << endl;
}

void MyIpv4Address::num2address(){
    address[0] = 0;
    address[1] = 0;
    address[2] = 0;
    address[3] = 0;

    for(int i=0; i<4; i++){
        int n=1;
        for(int j=0; j<8; j++){
            address[i] += (addNumber % 2) * n;
            addNumber >>= 1;
            n <<= 1;
        }
    }
}

void MyIpv4Address::address2num(){
    int n = 1;
    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            addNumber += address[i]%2 * n;
            address[i] >>= 1;
            n <<= 1;
        }
    }
}

void MyIpv4Address::string2address(char add[]){
    // Get length of ip_string
    int lenOfStr;
    for(int i=0; i<16; i++)
        if((int)add[i] < 46 || (int)add[i] > 57 || (int)add[i] == 47){
            lenOfStr = i-1;
            break;
        }

    // Split and save
    int n = 1;
    int index = 0;
    for(int i=lenOfStr; i>=0; i--){
        if((int)add[i] == 46){
            index++;
            n = 1;
        } else{
            address[index] += n * ((int)add[i]-48);
            n *= 10;
        }
    }
}
