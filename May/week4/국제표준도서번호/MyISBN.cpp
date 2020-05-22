#include "cstring"
#include "MyISBN.h" 

#include<iostream>
using namespace std;

MyISBN::MyISBN(){
    isbn[0] = '\0';
}

MyISBN::MyISBN(char isbn_number[]){
    strcpy(isbn, isbn_number);
}

bool MyISBN::isCorrectNumber() const{
    return isSyntaxValid() && isCheckSumValid();
}

bool MyISBN::isSyntaxValid() const{
    unsigned int lengthOfPart[] = {0, 0, 0, 0};
    int countHyphen = 0;
    for(int i=0; i<max_length+11; i++){
        // End of string (Null)
        if((int)isbn[i] == 0) break;
        // Too many hyphens or multiple hyphens
        if(isbn[i] == '-'){
            if(lengthOfPart[countHyphen] == 0 || ++countHyphen > 3)
                return false;
        }
        // non_number
        else if((int)isbn[i] < 48 || (int)isbn[i] > 57){
            // Exception checksum char
            if(countHyphen == 3 && isbn[i] == 'X'){
                lengthOfPart[countHyphen]++;
                continue;
            }
            return false;
        }else
            lengthOfPart[countHyphen]++;
    }
    // Too little hyphens
    if(countHyphen < 3) return false;
    // Too many number
    if(lengthOfPart[0] > 5) return false;
    if(lengthOfPart[1] > 7) return false;
    if(lengthOfPart[2] > 6) return false;
    if(lengthOfPart[3] != 1) return false;
    // Wrong length
    if( lengthOfPart[0] +
        lengthOfPart[1] +
        lengthOfPart[2] +
        lengthOfPart[3] != 10 )
        return false;
    // Corect case
    return true;
}

bool MyISBN::isCheckSumValid() const{
    int m = 10;
    int sum = 0;
    int i;
    int countHyphen = 0;
    for(i=0; i<=10; i++){
        if(isbn[i] == '-') continue;
        sum += ((int)isbn[i]-48) * m--;
    }

    int checkSum = 0;
    while((sum+checkSum)%11 != 0)
        checkSum++;

    if(checkSum == 10)
        return isbn[12] == 'X';
    return (int)isbn[12] == checkSum + 48;
}
