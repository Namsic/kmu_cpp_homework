#include<iostream>
using namespace std;

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int m, n;
        cin >> m >> n;
        int input1[m][n], input2[m][n];

        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                cin >> input1[i][j];
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                cin >> input2[i][j];

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cout << input1[i][j] + input2[i][j];
                if(j!=n-1)
                    cout << ' ';
            }
            cout << endl;
        }

    }
    return 0;
}


