#include<iostream>
using namespace std;

int abs(int n);
int euclideanDistance(int x1, int y1, int x2, int y2);
int rectilinearDistance(int x1, int y1, int x2, int y2);
void getDistance(int rectangle[], int dot[]);
void getDistance2(int rectangle[], int dot[]);
int getNearDot(int min, int max, int val);

int main(){
    int t;
    cin >> t;

    for(int i=0;i<t;i++){
        int rectangle[4], dot[2];  // rectangle: leftTop(x, y) & rightBottom(x, y)
        // input coordinate
        for(int j=0;j<4;j++)
            cin >> rectangle[j];
        for(int j=0;j<2;j++)
            cin >> dot[j];

        getDistance2(rectangle, dot);
    }

    return 0;
}


void getDistance(int rectangle[], int dot[]){
    int e_dis_min = euclideanDistance(rectangle[0], rectangle[1], dot[0], dot[1]);
    int r_dis_min = rectilinearDistance(rectangle[0], rectangle[1], dot[0], dot[1]);

    for(int x=rectangle[0];x<=rectangle[2];x++)
        for(int y=rectangle[1];y<=rectangle[3];y++){
            int e_dis = euclideanDistance(x, y, dot[0], dot[1]);
            int r_dis = rectilinearDistance(x, y, dot[0], dot[1]);
            if(e_dis_min > e_dis)
                e_dis_min = e_dis;
            if(r_dis_min > r_dis)
                r_dis_min = r_dis;
        }

    cout << e_dis_min << ' ' << r_dis_min << endl;
}


void getDistance2(int rectangle[], int dot[]){
    int x, y;
    x = getNearDot(rectangle[0], rectangle[2], dot[0]);
    y = getNearDot(rectangle[1], rectangle[3], dot[1]);

    cout << euclideanDistance(x, y, dot[0], dot[1]) << ' ';
    cout << rectilinearDistance(x, y, dot[0], dot[1]) << endl;
}

int getNearDot(int min, int max, int val){
    if(val < min)
        return min;
    if(val > max)
        return max;
    return val;
}



int euclideanDistance(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

int rectilinearDistance(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

int abs(int n){
    return n<0 ? n*-1 : n;
}
