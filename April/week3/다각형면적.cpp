#include<iostream>
using namespace std;

int abs(int n);
int area(int x[], int y[], int n);

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int n;
        cin >> n;
        int input_x[n+1], input_y[n+1], output;

        for(int j=0; j<n; j++){
            cin >> input_x[j];  // x_position
            cin >> input_y[j];  // y_position
        }
        input_x[n] = input_x[0];  // xn == x0
        input_y[n] = input_y[0];  // yn == y0

        output = area(input_x, input_y, n);
        cout << output << endl;
    }
    return 0;
}

int abs(int n){
    return n > 0 ? n : n * -1;
}


int area(int x[], int y[], int n){
    int res = 0;
    for(int i=0; i<n; i++)
        res += (x[i]+x[i+1]) * (y[i+1]-y[i]);

    cout << abs(res) << ' ';

    return abs(res)/res; // return res's sign
}
