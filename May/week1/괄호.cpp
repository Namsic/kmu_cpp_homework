#include<iostream>
using namespace std;

bool checkParenthesis(string str);

class charStack{
public:
    char arr[100];
    int cur;
    charStack(){
        cur = -1;
    }
    char pop(){
        if(cur >= 0)
            return arr[cur--];
        else  // Error
            return 'E';
    }

    void push(char c){
        arr[++cur] = c;
    }

    bool isEmpty(){
        return cur==-1;
    }
};

int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        // ----- input value ----- //
        string input;
        cin >> input;

        // ----- calculate ----- //
        bool result = checkParenthesis(input);

        // ----- output result ----- //
        cout << result << endl;

    }
    return 0;
}

bool checkParenthesis(string str){
    charStack st = charStack();
    
    for(int i=0; i<str.size(); i++){
        if(str[i] == '(' || str[i] == '{' || str[i] == '['){
            st.push(str[i]);
        }
        else if(str[i] == ')' && st.pop() != '('){
            return false;
            }
        else if(str[i] == '}' && st.pop() != '{'){
            return false;
            }
        else if(str[i] == ']' && st.pop() != '['){
            return false;
            }
    }
    return st.isEmpty();
}
