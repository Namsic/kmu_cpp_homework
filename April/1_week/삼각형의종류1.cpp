#include<iostream>
using namespace std;

int classify(int tri[]);
void sortLength(int length[]);
void swapInt(int *v1, int *v2);

int main(){
    int t;
    cin >> t;

    for(int i=0;i<t;i++){
        int tri[3];
        // input coordinate
        for(int j=0;j<3;j++){
            cin >> tri[j];
        }

        cout << classify(tri) << endl;
    }

    return 0;
}

int classify(int tri[]){
    sortLength(tri);
    if(tri[0] >= tri[1] + tri[2])
        return 0;

    if(tri[0] == tri[1] && tri[0] == tri[2])
        return 1;

    if(tri[0]*tri[0] == tri[1]*tri[1] + tri[2]*tri[2])
        return 2;

    if(tri[0] == tri[1] || tri[1] == tri[2] || tri[2] == tri[0])
        return 3;

    return 4;
}



void sortLength(int length[]){
    for(int i=1;i<3;i++){
        if(length[i]>length[0])
            swapInt(&length[0], &length[i]);
    }
}

void swapInt(int *v1, int *v2){
    int tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}
