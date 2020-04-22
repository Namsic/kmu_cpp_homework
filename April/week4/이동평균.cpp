#include<iostream>
using namespace std;

void movingAverage(int nums[], int n, int k);

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int len, interval;
        int output;

        cin >> len;
        int nums[len];
        for(int i=0;i<len;i++)
            cin >> nums[i];
        cin >> interval;

        movingAverage(nums, len, interval);
    }
    return 0;
}

void movingAverage(int nums[], int n, int k){
    int y;
    cout << n-k+1;
    for(int i=0;i<n-k+1;i++){
        y = 0;
        for(int j=i;j<k+i;j++){
            y += nums[j];
        }
        y /= k;

        cout << " " << y;
    }
    cout << endl;
}
