#include<iostream>
using namespace std;

int get_roomsize(bool floor[], int w, int h, int r, int c);
void sort_array(int arr[], int n);

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int m, n;
        // ----- input value ----- //
        cin >> m >> n;

        /* floor: map array
         * 0: need explore
         * 1: wall or already explored
         */
        bool floor[n*m];

        string input;
        for(int i=0;i<n;i++){
            cin >> input;
            for(int j=0;j<m;j++)
                floor[i*m + j] = input[j] == '+';
        }


        // ----- calculate ----- //
        int num_of_room = 0;
        int size_of_room[100];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!floor[i*m + j]){
                    size_of_room[num_of_room++] = get_roomsize(floor, m, n, i, j);
                }
            }
        }

        sort_array(size_of_room, num_of_room);

        // ----- output result ----- //
        cout << num_of_room << endl;
        for(int i=0; i<num_of_room; i++){
            cout << size_of_room[i];
            if(i == num_of_room-1)
                cout << endl;
            else
                cout << " ";
        }

    }
    return 0;
}

int get_roomsize(bool floor[], int w, int h, int r, int c){
    // floor[i][j] == floor[ (i)*w + (j) ]
    floor[r*w + c] = true;
    int result = 1;
    // Check up
    if(r > 0 and !floor[(r-1)*w + c]){
        result += get_roomsize(floor, w, h, r-1, c);
    }
    // Check down
    if(r < h-1 and !floor[(r+1)*w + c]){
        result += get_roomsize(floor, w, h, r+1, c);
    }
    // Check left
    if(c > 0 and !floor[r*w + c-1]){
        result += get_roomsize(floor, w, h, r, c-1);
    }
    // Check right
    if(c < w-1 and !floor[r*w + c+1]){
        result += get_roomsize(floor, w, h, r, c+1);
    }
    return result;
}

void sort_array(int arr[], int n){
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(arr[i] < arr[j]){
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
}
