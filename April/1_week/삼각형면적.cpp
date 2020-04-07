#include<iostream>
using namespace std;

int classify(int tri[]);
int abs(int n);

int main(){
    int t;
    cin >> t;

    for(int i=0;i<t;i++){
        int tri[6];
        // input coordinate
        for(int j=0;j<6;j++){
            cin >> tri[j];
        }

        cout << classify(tri) << endl;
    }

    return 0;
}

int classify(int tri[]){
    int size = (tri[2]-tri[0])*(tri[5]-tri[1]) - (tri[4]-tri[0])*(tri[3]-tri[1]);
    cout << abs(size) << ' ';
    
    if(size > 0)
        return 1;
    if(size < 0)
        return -1;
    if(size == 0)
        return 0;
}


int abs(int n){
    if(n<0)
        return n * -1;
    return n;
}
