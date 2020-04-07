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

        cout << cross(line1, line2) << endl;
    }

    return 0;
}



int cross(int line1[], int line2[]){
    int res =0;

    // line 1 is vertical line & line 2 is horizontal line
    // line 1 (x1 == x2) & line 2 (y1 == y2)
    if (line1[0] == line1[2]){
        if (inArea(line1[1], line1[3], line2[1]) == 0 || inArea(line2[0], line2[2], line1[0]) == 0)
            return 0;
        else if (inArea(line1[1], line1[3], line2[1]) == 2 || inArea(line2[0], line2[2], line1[0]) == 2)
            return 2;
        else
            return 1;
    }
    // line 2 is vertical line & line 1 is horizontal line
    // line 2 (x1 == x2) & line 1 (y1 == y2)
    if (line2[0] == line2[2]){
        if (inArea(line2[1], line2[3], line1[1]) == 0 || inArea(line1[0], line1[2], line2[0]) == 0)
            return 0;
        else if (inArea(line2[1], line2[3], line1[1]) == 2 || inArea(line1[0], line1[2], line2[0]) == 2)
            return 2;
        else
            return 1;
    }


    return res;
}

int inArea(int n1, int n2, int val){
    int max, min, res;
    if( n1 > n2 ){
        max = n1;
        min = n2;
    }else{
        max = n2;
        min = n1;
    }
    if( val<min || val>max )
        res = 0;
    if( min==val || max==val )
        res = 2;
    else
        res = 1;
    return res;
}
