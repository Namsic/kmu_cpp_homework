#include <iostream>
#include "MyISBN.h"
using namespace std;

int main(){
    int numTestCases;

    cin >> numTestCases;

    for(int i=0; i<numTestCases; i++){
        char isbn[max_length+1];

        cin >> isbn;

        MyISBN bookNumber(isbn);
        cout << bookNumber.isCorrectNumber() << endl;
    }
    return 0;
}
