#include<iostream>
using namespace std;

int hammingNum(int num);
void pullArray(int arr[], int n);

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int input, output;
        cin >> input;

        output = hammingNum(input);

        cout << output << endl;
    }
    return 0;
}

int hammingNum(int num){
    // hamming_list (left: small, right: large)
    int list_size = 300;
    int h[list_size];
    for(int i=0;i<list_size;i++)
        h[i] = 1;
    // h[0] is hamming[index]
    int index = 0;
    // largest number index
    int cursor = 0;

    while(true){
        if(num <= index+cursor+1)
            return h[num-index-1];

        while(h[0]*5 < h[cursor]){
            pullArray(h, list_size);
            index++;
            cursor--;
        }
        
        while(cursor < list_size-1){
            int min = h[cursor]*5;
            for(int i=0;i<=cursor;i++){
                if(h[i]*2 > h[cursor] && h[i]*2 < min)
                    min = h[i]*2;
                if(h[i]*3 > h[cursor] && h[i]*3 < min)
                    min = h[i]*3;
                if(h[i]*5 > h[cursor] && h[i]*5 < min)
                    min = h[i]*5;
            }
            h[++cursor] = min;
        }

    }
}

void pullArray(int arr[], int n){
    for(int i=0;i<n-1;i++){
        arr[i] = arr[i+1];
    }
    arr[n-1] = arr[n-2];
}
