#include "puzzle.h"

class Tester{//this is your tester class, you add your test functions in this class
public:
    bool testCopyConstructor(const Puzzle& puzzle);
    void measureInsertionTime(int numTrials, int N);
    void measureCopyConstructor();
    bool testParamConstructor(int size);
    bool testAssignOprt(const Puzzle& puzzle);
    bool testSelfAssignment();
};

int main() {

    cout << "lets see..."<< endl;
    Tester tester1;
    {
        //test constructor, size greater than 0
        cout << "\nTest case, Constructor: Size 100:" << endl;
        if (tester1.testParamConstructor(100)) cout << "Constructor passed!" << endl;
        else cout << "Constructor failed!" << endl;
    }
    {
        //test constructor, size less than 0
        cout << "\nTest case, Constructor: Size -7:" << endl;
        if (tester1.testParamConstructor(-7)) cout << "Constructor passed!" << endl;
        else cout << "Constructor failed!" << endl;
    }
    {
        //test constructor, size = 0
        cout << "\nTest case, Constructor: Size 0:" << endl;
        if (tester1.testParamConstructor(0)) cout << "Constructor passed!" << endl;
        else cout << "Constructor failed!" << endl;
    }
    cout << "*******************************************************************" <<endl;
    cout << "****************************Next Test******************************" <<endl;
    cout << "*******************************************************************" <<endl;
    Tester tester2;
    {
        //test deep copy, object with many members
        Puzzle p1(100);
        cout << "Test case, Copy Constructor: same members, same size, different pointers (deep copy):" << endl;
        if (tester2.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //test the edge case, object with 1 member
        cout << "\nTest case, Copy Constructor: 1 member:" << endl;
        Puzzle p1(1);
        if (tester2.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //test the edge case, 0 member, i.e. empty object
        cout << "\nTest case, Copy Constructor: zero members:" << endl;
        Puzzle p1(0);
        if (tester2.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    {
        //test the user error case, creating object with table zise less than 0
        cout << "\nTest case, Copy Constructor: table size less than 0:" << endl;
        Puzzle p1(-10);
        if (tester2.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
        else cout << "Copy constructor failed!" << endl;
    }
    cout << "*******************************************************************" <<endl;
    cout << "****************************Next Test******************************" <<endl;
    cout << "*******************************************************************" <<endl;
    Tester tester3;
    {
        //test deep copy, object with many members using Assignment Operator
        Puzzle p1(100);
        cout << "Test case, Assignment Operator: same members, same size, different pointers (deep copy):" << endl;
        if (tester3.testAssignOprt(p1)) cout << "Assignment Operator passed!" << endl;
        else cout << "Assignment Operator failed!" << endl;
    }
    {
        //test the edge case, object with 1 member
        cout << "\nTest case, Assignment Operator: 1 member:" << endl;
        Puzzle p1(1);
        if (tester3.testAssignOprt(p1)) cout << "Assignment Operator passed!" << endl;
        else cout << "Assignment Operator failed!" << endl;
    }
    {
        //test the edge case, 0 member, i.e. empty object
        cout << "\nTest case, Assignment Operator: zero members:" << endl;
        Puzzle p1(0);
        if (tester3.testAssignOprt(p1)) cout << "Assignment Operator passed!" << endl;
        else cout << "Assignment Operator failed!" << endl;
    }
    {
        //test the user error case, creating object with table size less than 0
        cout << "\nTest case, Assignment Operator: table size less than 0:" << endl;
        Puzzle p1(-10);
        if (tester3.testAssignOprt(p1)) cout << "Assignment Operator passed!" << endl;
        else cout << "Assignment Operator failed!" << endl;
    }
    {
    //testing with self assignment
    cout << "\nTest case, Assignment Operator: self assignment:" << endl;
    if (tester3.testSelfAssignment()) cout << "self assignment passed!" << endl;
    else cout << "self assignment failed!" << endl;
    }

    cout << "*******************************************************************" <<endl;
    cout << "****************************Next Test******************************" <<endl;
    cout << "*******************************************************************" <<endl;

    {
        //Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M = 5;//number of trials
        int N = 1000;//original input size
        tester3.measureInsertionTime(M, N);
    }
    {
        //Measuring the efficiency of copy constructor
        cout << "\nMeasuring the efficiency of copy constructor:" << endl;
        tester3.measureCopyConstructor();
    }
    {
        //an example of dump
        cout << "\nHere is an example of a table:" << endl;
        Puzzle p1(10);
        p1.dump();
        cout << endl;
    }
    return 0;
}



bool Tester::testCopyConstructor(const Puzzle& puzzle){
    Puzzle copy(puzzle);
    //the case of empty object
    if (puzzle.m_size == 0 && copy.m_size == 0) return true;
        //the case that sizes are the same and the table pointers are not the same
    else if (puzzle.m_size == copy.m_size && puzzle.m_table != copy.m_table){
        for (int i=0;i<puzzle.m_size;i++){
            for (int j=0;j<puzzle.m_size;j++)
            {
                if ((puzzle.m_table[i][j] != copy.m_table[i][j]) || //check the value
                    (puzzle.m_table[i] == copy.m_table[i])){        //check the ith pointer
                    return false;
                }
            }
        }
        return true;
    }
        //everything else
    else return false;
}
void Tester::measureInsertionTime(int numTrials, int N)
{
    //Measuring the efficiency of insertion algorithm with system clock ticks
    //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
    //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials-1;k++)
    {
        start = clock();
        Puzzle p1(N);//the algorithm to be analyzed for efficiency
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N * N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}
void Tester::measureCopyConstructor(){

    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    int N = 10;
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<5;k++)
    {
        Puzzle toBeCopied(N);
        start = clock();
        Puzzle copy(toBeCopied);
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N * N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }

}

bool Tester::testParamConstructor(int size){
    //Testing the constructor
    //this also tests:
    //makeMem() and fill()
    //Test Cases:
    //if m_size < 0 , puzzle(int size) takes care of this to set to 0
    //if m_size = 0 , invalid entry throw exception
    //if m_size > 0 , allocate memory
    Puzzle testP(size);
    if (testP.m_size == 0 && testP.m_table == nullptr) { //if m_size < 0, if m_size = 0
        return true;                                     //return true
    }
    else if (testP.m_size == size){                       //if m_size > 0, check size is true
        return true;
    }else
    return false;                                        //otherwise we fail

}

bool Tester::testAssignOprt(const Puzzle& puzzle){
    //Test Cases:
    //if case of empty object
    //if self assignment
    //the case that sizes are the same and the table pointers are not the same
    Puzzle oprtCopy = puzzle;
    //the case of empty object
    if (puzzle.m_size == 0 && oprtCopy.m_size == 0) return true;
        //the case that sizes are the same and the table pointers are not the same
    else if (puzzle.m_size == oprtCopy.m_size && puzzle.m_table != oprtCopy.m_table){
        for (int i=0;i<puzzle.m_size;i++){
            for (int j=0;j<puzzle.m_size;j++)
            {
                if ((puzzle.m_table[i][j] != oprtCopy.m_table[i][j]) || //check the value
                    (puzzle.m_table[i] == oprtCopy.m_table[i])){        //check the ith pointer
                    return false;
                }
            }
        }
        return true;
    }
        //everything else
    else return false;
}

bool Tester::testSelfAssignment() {
    Puzzle p1(10);
    char **temp = p1.m_table;
    //cout << "Original address value: " << p1.m_table <<endl;
    p1 = p1;
    //cout << "Original address value: " << p1.m_table <<endl;
    if (p1.m_table == temp){ //if original address did not change, self assignment did not occur
        return true;
    }
    return false;
}