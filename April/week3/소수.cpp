#include<iostream>
#include<math.h>
using namespace std;

int checkNum(int num);

int main(){
    int t;
    cin >> t;

    for(int i=0;i<t;i++){
        int input, output;
        cin >> input;
        output = checkNum(input);
        cout << output << endl;
    }
    return 0;
}

int checkNum(int num){
    int res = 1;
    for(int i=2;i<=num/2;i++)
        if(num%i == 0)
            res = 0;
    return res;
}

