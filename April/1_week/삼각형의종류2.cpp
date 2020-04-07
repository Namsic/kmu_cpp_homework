#include<iostream>
using namespace std;

int classify(int tri[]);
void sortLength(int length[]);
void swapInt(int *v1, int *v2);
bool isPosible(int tri[]);
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
    if(!isPosible(tri))
        return 0;

    int len[3];
    // dot0 ~ dot1
    len[0] = (tri[0]-tri[2])*(tri[0]-tri[2]) + (tri[1]-tri[3])*(tri[1]-tri[3]);
    // dot0 ~ dot1
    len[1] = (tri[2]-tri[4])*(tri[2]-tri[4]) + (tri[3]-tri[5])*(tri[3]-tri[5]);
    // dot0 ~ dot1
    len[2] = (tri[4]-tri[0])*(tri[4]-tri[0]) + (tri[5]-tri[1])*(tri[5]-tri[1]);

    sortLength(len);

    if(len[0] == len[1]+len[2])
        return 1;
    if(len[0] > len[1]+len[2])
        return 2;
    if(len[0] < len[1]+len[2])
        return 3;
}

bool isPosible(int tri[]){
    // use slope
    double slope[3];
    
    // dot0 and dot1
    if(tri[1]==tri[3])
        slope[0] = -1;
    else
        slope[0] = (double)abs(tri[0]-tri[2])/abs(tri[1]-tri[3]);
    // dot1 and dot2
    if(tri[3]==tri[5])
        slope[1] = -1;
    else
        slope[1] = (double)abs(tri[2]-tri[4])/abs(tri[3]-tri[5]);
    // dot2 and dot0
    if(tri[5]==tri[1])
        slope[2] = -1;
    else
        slope[2] = (double)abs(tri[4]-tri[0])/abs(tri[5]-tri[1]);


    if(slope[0] == slope[1])
        return false;
    if(slope[1] == slope[2])
        return false;
    if(slope[2] == slope[0])
        return false;
    return true;
}

int abs(int n){
    if(n<0)
        return n*-1;
    else
        return n;
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
