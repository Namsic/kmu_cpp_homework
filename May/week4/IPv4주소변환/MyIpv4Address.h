#ifndef _MY_IPV4_ADDRESS_H_
#define _MY_IPV4_ADDRESS_H_

class MyIpv4Address{
public:
    MyIpv4Address();
    MyIpv4Address(unsigned int num);
    MyIpv4Address(char add[]);

    void printAddress() const;
    void printNumber() const;

private:
    unsigned int addNumber;
    unsigned char address[4];

    void num2address();
    void address2num();
    void string2address(char add[]);
};

#endif // _MY_IPV4_ADDRESS_H_
