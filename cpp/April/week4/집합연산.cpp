#include<iostream>
using namespace std;


unsigned int power(int n, int p);
void set_intersection(unsigned int set1[], unsigned int set2[]);
void set_union(unsigned int set1[], unsigned int set2[]);
void set_difference(unsigned int set1[], unsigned int set2[]);
void print_set(unsigned int set[]);

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        int size;
        unsigned int set_1[] = {0, 0, 0, 0, 0}, set_2[] = {0, 0, 0, 0, 0};
        int output;

        int n;
        cin >> size;
        for(int i=0;i<size;i++){
            cin >> n;
            set_1[n/32] += power(2, n%32);
        }
        cin >> size;
        for(int i=0;i<size;i++){
            cin >> n;
            set_2 [n/32] += power(2, n%32);
        }

        set_intersection(set_1, set_2);
        set_union(set_1, set_2);
        set_difference(set_1, set_2);

    }
    return 0;
}

unsigned int power(int n, int p){
    unsigned int res = 1;
    for(int i=0;i<p;i++)
        res *= n;
    return res;
}


void set_intersection(unsigned int set1[], unsigned int set2[]){
    unsigned int res[5];
    for(int i=0;i<5;i++)
        res[i] = set1[i] & set2[i];
    print_set(res);
}

void set_union(unsigned int set1[], unsigned int set2[]){
    unsigned int res[5];
    for(int i=0;i<5;i++)
        res[i] = set1[i] | set2[i];
    print_set(res);
}

void set_difference(unsigned int set1[], unsigned int set2[]){
    unsigned int res[5];
    for(int i=0;i<5;i++)
        res[i] = set1[i] - (set1[i] & set2[i]);
    print_set(res);
}

void print_set(unsigned int set[]){
    int res[132], cnt = 0;

    for(int i=0;i<5;i++){
        int n = 0;
        while(set[i] > 0){
            if(set[i]%2 == 1)
                res[cnt++] = i*32 + n;
            set[i] = set[i] >> 1;
            n++;
        }
    }

    cout << cnt;
    for(int i=0;i<cnt;i++){
        cout << " " << res[i];
    }
    cout << endl;
}
