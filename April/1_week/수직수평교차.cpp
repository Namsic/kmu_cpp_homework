#include<iostream>
using namespace std;

int cross(int line1[], int line2[]);
int inArea(int n1, int n2, int val);

int main(){
    int t;
    cin >> t;

    for(int i=0;i<t;i++){
        int line1[4], line2[4];

        // input coordinate
        for(int j=0;j<4;j++){
            cin >> line1[j];
        }
        for(int j=0;j<4;j++){
            cin >> line2[j];
        }
        
        // sort coordinate
        sortLine(line1);
        sortLine(line2);

        cout << cross(line1, line2) << endl;
    }

    return 0;
}



int cross(int line1[], int line2[]){
    if(line1[0] == line1[2]){
        int _1x = line1[0];
        int _2y = line1[1];
        for(int _1y=line1[1]; _1y<=line1[3]; _1y++)
            for(int _2x=line2[0]; _2x<=line2[2]; _2x++)
                if(_1x == _2x && _1y == _2y){
                    if((_1y == line1[1] || _1y == line1[3]) || (_2x == line2[0] || _2x == line2[2]))
                        return 2;
                    else
                        return 1;
                }
        return 0;
    }
    
    if(line1[1] == line1[3]){
        int _1y = line1[1];
        int _2x = line2[0];
        for(int _1x=line1[0]; _1x<=line1[2]; _1x++)
            for(int _2y=line2[1]; _2y<=line2[3]; _2y++)
                if(_1x == _2x && _1y == _2y){
                    if( (_1x == line1[0] || _1x == line1[2]) || (_2y == line2[1] || _2y == line2[3]) )
                        return 2;
                    else
                        return 1;
                }
        return 0;
    }
}

void sortLine(int line[]){
    if(line[0] == line[2] && line[1] > line[3])
        swapInt(line[1], line[3]);
    if(line[1] == line[3] && line[0] > line[2])
        swapInt(line[0], line[2]);
}

void swapInt(int *v1, int *v2){
    int tmp;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}
