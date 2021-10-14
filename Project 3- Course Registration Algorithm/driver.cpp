// CMSC 341 - Spring 2021 - Project 3
// driver.cpp: sample driver for the RQueue class.

#include "rqueue.h"
using namespace std;
// Priority functions compute an integer priority for a student. Internal
// computations may be floating point, but must return an integer.
class Tester {
public:
    void insertionPerformance(int numTrials, int N, prifn_t prior);
    void randomFunctionsTester(RQueue &queue);
};

void Tester::insertionPerformance(int numTrials, int N, prifn_t prior){
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    clock_t startD, stopD;
    for (int k=0;k<numTrials -1;k++)
    {
        Student fill[N];
        int priority =1; //1-6
        int year =0; //0-3
        int major = 0; //0-2
        int group = 0; // 0-1
        for(int i=0; i < N ;i++) {      //this function creates new students periodically, the students are inserted into an array
            fill[i] = Student("Name", priority, year, major, group);
            //basically goes through the limits of the student objects and resets the variables based on that
            if(priority == 6){
                priority=0;
            }
            if(year == 3){
                year=-1;
            }
            if(major == 2){
                major=-1;
            }
            if(group == 1){
                group=-1;
            }
            priority++;
            year++;
            major++;
            group++;

        }

        RQueue p1(prior);           //the algorithm to be analyzed for efficiency
        start = clock();            //start clock for insertion
        for(int i=0; i < N;i++){
            p1.insertStudent(fill[i]);
        }

        stop = clock();             //stop clock for insertion
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;

        startD = clock();           //start clock for deletion
        for(int i=0; i < N;i++){
            p1.getNextStudent();
        }

        stopD = clock();            //stop clock for deletion
        T = stopD - startD;
        cout << "Deletion " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}

void Tester::randomFunctionsTester(RQueue &queue) {
    cout<< "\nPrint the size of the queue: ";
    cout << queue._size<<endl;
    cout<< "\nPrint the number of students in the queue: ";
    cout << queue.numStudents()<<endl;
}

int priorityFn1(const Student &student);
int priorityFn2(const Student &student);

int main() {

    RQueue queue1(priorityFn1);
    RQueue queue2(priorityFn1);

    // Create some test students and insert them into the queue
    //Student(string name, int priority, int year, int major, int group)
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    Student student3("Nick",2,0,0,0);
    Student student4("Eva",4,3,2,1);

    queue1.insertStudent(student3);
    queue1.insertStudent(student1);
    queue1.insertStudent(student2);
    queue1.insertStudent(student4);

    std::cout << "\nqueue1 dump after inserting 4 students (Nick, Sam, Liz, Eva):" << std::endl;
    queue1.dump();

    Student student5("John",6,3,2,1);
    Student student6("Mia",3,0,0,0);

    queue2.insertStudent(student5);
    queue2.insertStudent(student6);

    std::cout << "\nqueue2 dump after inserting 2 students (John, Mia):" << std::endl;
    queue2.dump();



    // Merge the two queues together and print the resulting tree

    queue1.mergeWithQueue(queue2);

    std::cout << std::endl << "Contents of queue1 after merging with queue2:\n";
    queue1.printStudentQueue();
    std::cout << "\nDump queue1 after merging with queue2:\n";
    queue1.dump();
    cout << "Showing queue 2 is empty: ";
    queue2.dump();

    // Print the queue, change priority function, print again, change
    // again, print again.  Changing the priority function should cause
    // the heap to be rebuilt.
    queue1.setPriorityFn(priorityFn2);

    std::cout << std::endl << "Contents of queue1 after changing the priority function to priorityFn2:\n";
    queue1.printStudentQueue();
    std::cout << "\nDump queue1 after changing the priority function to priorityFn2:\n";
    queue1.dump();

    queue1.setPriorityFn(priorityFn1);

    std::cout << std::endl << "Contents of queue1 after changing the priority function back to priorityFn1:\n";
    queue1.printStudentQueue();
    std::cout << "\nDump queue1 after changing the priority function back to priorityFn1:\n";
    queue1.dump();


    //testing the removal function, using a try catch block to test deletion of an empty queue
    std::cout << "\nFinal queue1 in priority order:\n";
    while (queue1.numStudents() > 0 ) {
        Student student = queue1.getNextStudent();
        std::cout << "[" << priorityFn1(student) << "] " << student << std::endl;
    }
    try {
        Student student = queue1.getNextStudent();
    }catch(exception& e){
        cerr << "exception: " << e.what() << endl;
        cout << "Deletion of an empty queue: test passed"<<endl;
    }


    //now queue 1 is empty and so is queue 2
    cout << "\nShowing queue 1 is empty: ";
    queue1.dump();
    cout << "Showing queue 2 is empty: ";
    queue2.dump();

    cout << "\nLets begin copy constructor and assignment override testing: \n";
    //insert students into queue1
    queue1.insertStudent(student1);
    queue1.insertStudent(student2);
    queue1.insertStudent(student3);
    queue1.insertStudent(student4);
    cout << "Show the content of queue1 so far: \n";
    queue1.dump();
    //test the = override of the same priority function
    RQueue copyTester(priorityFn1);    //creating a copy tester that is empty
    //copyTester.insertStudent(student5);
    cout << "Copying into an empty queue, showing that copy tester: ";
    copyTester.dump();
    cout << "Begin assignment override:  \n";
    copyTester = queue1;
    cout << "Show content of copyTester: \n";
    copyTester.dump();
    cout << "Add an element to copyTester and compare to original queue1: \n";
    Student student8("Joud",2,3,2,1);
    copyTester.insertStudent(student8);
    cout << "copyTester content: \n";
    copyTester.dump();
    cout << "O.G. queue1 content: \n";
    queue1.dump();

    cout << "\nBegin copy constructor testing:  \n";
    RQueue copyConTester(copyTester); //creating a new RQueue and copying the contents of copyTester into it
    cout << "Show the content of copyConTester:  \n";
    copyConTester.dump();
    cout << "Show the address of copyConTester:  \n";
    cout << &copyConTester <<endl;
    cout << "Show the address of copyTest:  \n";
    cout << &copyTester <<endl;

    Tester tester;
    cout << "\nTesting a case of an RQueue with a different priroty function being added:  \n";
    RQueue priortyCopyTest(priorityFn2);    //create a teser queue that is not empty
    priortyCopyTest.insertStudent(student5);
    priortyCopyTest.insertStudent(student6);
    Student student9("Joud",1,3,2,1);
    priortyCopyTest.insertStudent(student9);
    cout << "Show the content of priortyCopyTest:  \n";
    priortyCopyTest.dump();
    priortyCopyTest = copyTester;
    cout << "Show the content of priortyCopyTest after assignment to RQueue with a diffrent priority function:  \n";
    priortyCopyTest.dump(); //the tester changed its priority to the objects function that is being copied
    cout << "\nNow remove an element from priortyCopyTest for fun:  \n";
    Student student = priortyCopyTest.getNextStudent();
    cout << "[" << priorityFn1(student) << "] " << student << endl;
    priortyCopyTest.dump();
    cout << "\nHow many elements are in the queue?:";
    tester.randomFunctionsTester(priortyCopyTest);

    cout << "\nNow testing merging of two different priority :  \n";
    priortyCopyTest.setPriorityFn(priorityFn2);
    priortyCopyTest.dump();
    try{
        priortyCopyTest.mergeWithQueue(copyTester);
    }catch(exception& e){
        cerr << "exception: " << e.what() << endl;
        cout << "Merge two different priorities queues: test passed"<<endl;
    }

    {
        //Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M =7;//number of trials
        int N = 1000;//original input size
        tester.insertionPerformance(M, N, priorityFn1);
    }

    return 0;
}

int priorityFn1(const Student&student) {
    //priority value is determined based on some criteria
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    int priority = student.getYear() + student.getMajor() + student.getGroup();
    return priority;
}

int priorityFn2(const Student&student) {
    //priority is determined by an officer in registrar office
    //priority value falls in the range [0-6]
    //the smaller value means the higher priority
    return student.getPriority();
}