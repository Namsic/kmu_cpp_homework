#include<iostream>
using namespace std;

void multiplyMatrix(int mat1[], int mat2[], int r, int s, int t, int res[]);

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int r, s, t;

        cin >> r >> s >> t;
        int matrixA[r*s], matrixB[s*t];
        int result[r*t];

        // input r*s matrix
        for(int i=0;i<r;i++)
            for(int j=0;j<s;j++)
                cin >> matrixA[i*s + j];
        // input s*t matrix
        for(int i=0;i<s;i++)
            for(int j=0;j<t;j++)
                cin >> matrixB[i*t + j];

        // calculate
        // resust: r*t matrix
        multiplyMatrix(matrixA, matrixB, r, s, t, result);

        // print result
        for(int i=0;i<r;i++)
            for(int j=0;j<t;j++){
                cout << result[i*t + j];
                if(j == t-1)
                    cout << endl;
                else
                    cout << " ";
            }
    }
    return 0;
}

void multiplyMatrix(int mat1[], int mat2[], int r, int s, int t, int res[]){
    for(int i=0;i<r;i++)
        for(int j=0;j<t;j++){
            int sum = 0;
            for(int k=0;k<s;k++)
                sum += mat1[i*s + k] * mat2[k*t + j];
            res[i*t + j] = sum;
        }
}
