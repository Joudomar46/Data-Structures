#include <iostream>
//doubly linked list
//one pointer to the next node and to previous node
//allows to move front and back
//nodes point towards headers and trailer
/*
using namespace std;
#include <stack>

bool parseParent(char array[], int n);
void reverse(int array[], int arraySize);

bool parseParent(char array[], int n) {
    // ( 4 + (5 / 3 ) 10 )
    // ( 4 + ( 5 / 3 ) 10 )
    // 
    stack<char> aStack; //empty stack
    for (int i = 0; i < n ; i++) {
        if (array[i] == '(') { // if opening statement
            aStack.push(array[i]); //push ( to stack
        } else if (array[i] == ')') {
            if (aStack.empty()) { //empty stack
                return false;    //nothing to match
            }
            aStack.pop();//each time you get a closing ) you remove (
        }
    }
        if (aStack.empty()) //so if this not empty by the end, they dont match
            return true;
        else
            return false;
    }

void reverse(int array[], int arraySize) {

    int firstIndex = 0; // [ first , - , - , last ] // index of the front of the queue
    int lastIndex = arraySize - 1 ; //[lastvalue , - , - , firstvalue]  // index of the rear of array

    for (int i = 0; i < (arraySize/2); i++){
        int tempFront = array[firstIndex];
        array[firstIndex] = array[lastIndex]; //switch the values in the array back to front
        array[lastIndex] = tempFront; //switch values in array
        firstIndex++;
        lastIndex--;
    }
    for (int i = 0; i < arraySize; i++){
        cout << array[i] << ", ";
    }

}


int main() {
    char test[] = { '(', ')','(',')'};
    if (parseParent(test,4)){
        cout << "this is correct" <<endl;
    }
    else
        cout << "Nope" <<endl;

    int test2[6] = {1 , 2, 3, 4, 5, 6};
    reverse(test2, 6);

    return 0;
}
*/