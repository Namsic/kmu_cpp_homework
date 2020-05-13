#include<iostream>
#include<fstream>
#include<cstdlib>
#include"MyHammingDistance.h"
using namespace std;

int main(){
    int numTestCases;
    cin >> numTestCases;

    for(int i=0; i<numTestCases; i++){
        unsigned int num1, num2;
        cin >> num1 >> num2;

        MyBinaryNumber bn1(num1), bn2(num2);

        cout << bn1.getHammingWeight() << " " << bn2.getHammingWeight() << " "
             << bn1.getHammingDistance(bn2) << endl;
    }
    return 0;
}
