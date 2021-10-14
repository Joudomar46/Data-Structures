// CMSC 341 - Spring 2021 - Project 4
// driver.cpp
// Simple driver program for use with HashTable class
#include "hash.h"
#include <random>

// Using a fixed seed value generates always the same sequence
// of pseudorandom numbers, e.g. reproducing scientific experiments
// here it helps us with testing since the same sequence repeats
std::mt19937 generator(10);// 10 is the fixed seed value

// We distribute the pseudorandom numbers uniformaly within
// the range [1000,99999]
std::uniform_int_distribution<> distribution(1000, 99999);

// The hash function used by HashTable class
unsigned int hashCode(const string str);

// the function to generate random serial numbers
unsigned int vaccineSerial() {return distribution(generator);}

class Tester{ // Tester class to implement test functions
public:
    Tester(){}
    ~Tester(){}
    void insertionPerformance(int, int);
private:
};

void Tester::insertionPerformance( int N, int numTrials){
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    clock_t startD, stopD;
    for (int k=0;k < numTrials;k++) {
        HashTable testTableTime(N * 2, hashCode); //creating a hash table less than MIN
        start = clock();            //start clock for insertion
        for (int i = 0; i < N; i++) {
            testTableTime.insert(Person("Erica", i));
        }
        stop = clock();             //stop clock for insertion
        T = stop - start;//number of clock ticks the algorithm took

        cout << "Inserting " << testTableTime.m_size << " members took with table size " <<
        testTableTime.m_capacity << " took "<< T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!"
             << endl;

        N = N * a;//increase the input size by the scaling factor
    }
    }

int main(){




    // We use this temp array to store some data points for later use
    int tempSerials[50] = {0};
    int secondIndex = 0;
    // create a hash table with the size 101, and the hash function hashCode
    HashTable aTable(101,hashCode);
    int temp = 0;
    // we insert 50 Person objects with the same key, person's name is the key
    for (int i=0;i<50;i++){
        temp = vaccineSerial();// generates a random number
        if (i%3 == 0){//this saves 17 numbers from the generated numbers for later use
            tempSerials[secondIndex] = temp;
            cout << temp << " was saved for later use." << endl;
            secondIndex++;
        }
        // print the random numbers which are inserted
        cout << "Insertion # " << i << " => " << temp << endl;
        aTable.insert(Person("John", temp));
    }

   cout << "Message: dump after 50 insertions in a table with 101 buckets:" << endl;
   aTable.dump();

    // We insert a data point to change the load factor, this should initiate a rehash
    temp = vaccineSerial();
    cout << "Insertion # 51" << " => " << temp << endl;
    aTable.insert(Person("John", temp));
    cout << "Message: dump after 51st insertion, the rehash should have happended to a table with 211 buckets:" << endl;
    aTable.dump();



    // Now we remove some data points which were saved in tempSerials array
    // Deleting 13 data points changes the deleteRatio, it should initiate a rehash
    for (int i = 0;i<14;i++)
        aTable.remove(Person("John", tempSerials[i]));

    cout << "Message: dump after 14 removes, a rehash should have happened to a table with 157 buckets," << endl;
    cout << "Message: after 13 removals the rehash happens, then the 14th removal will be tagged as DELETED in the new table." << endl;
    aTable.dump();
    cout << endl;

    int tempRandom;
    HashTable testTable(50,hashCode); //creating a hash table less than MIN
    for (int i=0;i<50;i++) {
        tempRandom = vaccineSerial();// generates a random number
        cout << "Insertion # " << i << " => " << tempRandom << endl;
        testTable.insert(Person("Dalton", tempRandom));
    }
    testTable.dump();
    cout << "Showing table size is the default since size is less than MIN" << endl;
    cout << endl;
    cout << "Lets delete some objects in this array for later rehashing use" << endl;
    testTable.remove(Person("Dalton", 21875));
    cout << "Deleting the same person twice has no affect on the program:" << endl;
    testTable.remove(Person("Dalton", 21875));
    cout << "Deleting some thing that does not exist has no affect on the program:" << endl;
    testTable.remove(Person("bob", 50));
    testTable.remove(Person("Dalton", 58406));
    testTable.remove(Person("Dalton", 14903));
    testTable.remove(Person("Dalton", 20181));
    testTable.dump();
    cout << "Lets add another element to test if the rehash is triggered,\n"
            " we will see what happens with the deleted objects:" << endl;
    testTable.insert(Person("Dalton", 20181));
    testTable.dump();
    cout << "As you can see, the size of array doubled and the rehash was triggered,\n"
            " the first person was Deleted and it was ignored by the program. \n"
            "Dalton 80516 was inserted into the correct hash as the first index: " << endl;
    cout << hashCode("Dalton") % 211 << ". The second index is 94, the third is 93+2^2 % 4 = 97\n\n";
    cout << "Now lets add even more elements to trigger the switch back to Linear Probing:" << endl;
    for (int i=0;i<50;i++) {
        tempRandom = vaccineSerial();// generates a random number
        cout << "Insertion # " << i << " => " << tempRandom << endl;
        testTable.insert(Person("Rob", tempRandom));
    }
    testTable.dump();
    cout << "The trigger occurred, Notice that the keys also affect the index " << endl;
    Tester tester;
    //Measuring the efficiency of insertion functionality
    cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
    int M = 7;//number of trials
    int N = 100;//original input size
    tester.insertionPerformance(N, M);
    cout << "Check to see if trigger occured by setting probing policy function" << endl;
    testTable.setProbingPolicy(QUADRATIC);
    testTable.dump();
    //I wrote this in a day and a half, forgive my horrible tests its been a very long semester
    // but at least no memory leaks...I think lol
    //thank you for a crazy semester and have good finals week. Good luck!!
    return 0;
}

// The implementation of the hash function
// you can copy this function to your mytest.cpp file
unsigned int hashCode(const string str) {
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook
    for ( int i = 0 ; i < str.length(); i++) //4090
        val = val * thirtyThree + str[i] ;
    return val ;
}

