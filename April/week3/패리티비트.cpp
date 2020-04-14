#include<iostream>
using namespace std;

int countOne(int num);
unsigned int parityBit(int num);

int main(){
    int t;
    cin >> t;

    for(int i=0;i<t;i++){
        unsigned int input, output;
        cin >> input;
        output = parityBit(input);
        cout << output << endl;
    }
    return 0;
}

unsigned int parityBit(int num){
    int pb = 2147483648; // 2^31
    return countOne(num)%2 == 1? num + pb : num;
}

int countOne(int num){
    int cnt = 0;
    while( num > 0 ){
        if( num%2 == 1 )
            cnt++;
        num = num >> 1;
    }
    return cnt;
}
