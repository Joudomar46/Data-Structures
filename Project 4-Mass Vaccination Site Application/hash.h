// CMSC 341 - Spring 2021 - Project 4
// hash.h
// The interface of the Class HashTable
#ifndef _HASH_H
#define _HASH_H
#include <string>
#include <iostream>
#include "person.h"
using namespace std;
// Defined names
#define EMPTY Person("",0)              // This is an empty object
#define DELETED Person("DELETED", 0)    // This is a deleted object
#define DELETEDKEY "DELETED"            // This is a deleted key
enum probing {LINEAR, QUADRATIC};
const int MINPRIME = 101;   // Min size for hash table
const int MAXPRIME = 99991; // Max size for hash table
// the prototype of the function pointer, it points to the hash function
typedef unsigned int (*hash_fn)(string);
class Grader;// For grading purposes
class Tester;// For testing purposes, you write test functions in this class
class HashTable {
public:
    friend class Grader;
    friend class Tester;
    // Constructor,  requires table size and hash function.
    HashTable(unsigned size, hash_fn hash);
    // Destructor
    ~HashTable();
    // Returns table size
    unsigned int tableSize() const { return m_capacity; }
    // Returns number of entries in the table
    unsigned int numEntries() const { return m_size; }
    // Returns Load factor
    float lambda() const;
    // Returns the ratio of deleted buckets
    float deletedRatio() const;
    // Inserts person in the table
    bool insert(Person person);
    // Deletes person
    bool remove(Person person);
    // We can enforce a rehash by changing the probing policy
    void setProbingPolicy(probing prob);
    // Dumps the contents of the hash table, for debugging purposes
    void dump() const;

private:
    unsigned int    m_capacity;     // hash table size
    unsigned int    m_size;         // current number of entries
    unsigned int    m_numDeleted;   // number of deleted entries
    hash_fn         m_hash;         // pointer to the hash function
    Person*         m_table;        // hash table
    probing         m_currentProb;  // it is either LINEAR or QUADRATIC

    // Private helper functions
    // Checks whether number is a prime number
    bool isPrime(int number);
    // Returns the smallest prime number greater than current
    int findNextPrime(int current);

    /******************************************
    * Private function declarations go here! *
    ******************************************/
    //inline helper function to find empty indexes
    inline bool isEmpty(int index , Person * person){
        if(person[index] == EMPTY){
            return true;
        }else
            return false;
    }
    //probing helper function
    int whichProbing(int h, Person person, Person * hashTable);
};
#endif