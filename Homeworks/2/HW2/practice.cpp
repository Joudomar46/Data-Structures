#include <iostream>
//doubly linked list
//one pointer to the next node and to previous node
//allows to move front and back
//nodes point towards headers and trailer
using namespace std;
#include <stack>
bool parseParent(char array[], int n);

bool parseParent(char array[], int n) {
    // ( 4 + (5 / 3 ) 10 )
    // ( 4 + ( 5 / 3 ) 10 )
    //( 1 + 2 )
    stack<char> aStack; //empty stack
    stack<int> aOprtStack; //empty stack

    for (int i = 0; i < n; i++) {

        if (array[i] <= 57 && array[i] >= 48) { //take care of numbers
            int number = array[i] - '0';
            if (array[i + 1] <= 57 && array[i + 1] >= 48) {
                aOprtStack.push(number);
                cout << aOprtStack.top();
            }
            if (array[i] == '+' || array[i] == '-') {
                aStack.push(array[i]);
                cout << aStack.top();
            }

            if (array[i] == '(') { // if opening statement   // added ( and 1 and  2
                aStack.push(array[i]); //push ( to stack
                cout << aStack.top() << endl;
            } else if (array[i] == ')') {
                cout << endl;
                cout << endl;

                int toUse = aOprtStack.top(); // 2
                aOprtStack.pop(); //pop it
                aOprtStack.top() = aOprtStack.top() + toUse;
                aStack.pop();
                cout << aOprtStack.top() << endl;
                aStack.pop();

            }

        }
        if (aStack.empty()) //so if this not empty by the end, they dont match
            return true;
        else
            return false;
    }
}

using namespace std;
#include <stack>

int main() {
    char test[] = { '(', '1', '+' , '(', '9', '+' ,'2',')',')'};
    if (parseParent(test,9)){
        cout << "this is correct" <<endl;
    }
    else
        cout << "Nope" <<endl;


    return 0;
}