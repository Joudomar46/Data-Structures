// CMSC 341 - Spring 2021 - Project 4
// hash.cpp
// The implementation of the class HashTable
#include "hash.h"
#include "math.h"

HashTable::HashTable(unsigned size, hash_fn hash){
    //size of table and prime 4 cases
    //if less than min value set to min
    //if greater than max value set to max
    //if prime number set to number
    //if in between min and max value, find the next prime number after value
    if (size < MINPRIME){
        m_capacity = MINPRIME;
    }else if (size > MAXPRIME){
        m_capacity = MAXPRIME;
    }else if (isPrime(size)){
        m_capacity = size;
    }else{
        m_capacity = findNextPrime(size);
    }
    m_size = 0;     //occupied buckets
    m_numDeleted = 0; //marked as deleted buckets
    m_hash = hash;    //the pointer function hash
    m_table = new Person[m_capacity]; //create an array of persons
    for (int i = 0; i < m_capacity; i++) {
       m_table[i] = EMPTY;
    }
    m_currentProb = LINEAR;     //setting current probing to default linear
}

HashTable::~HashTable(){
    delete [] m_table; //love it when its this easy
}

//linearing probring
//treat deleted variables as occupied
//Hash collisions should be resolved using current probing
//policy which is set in m_currentProb.
bool HashTable::insert(Person person){
    bool success = false;
    //using the hash function to retrieve first index
    int h = m_hash(person.key()) % m_capacity;

    if(!isEmpty(h, m_table)){     //probing algorithm for first hash function is occupied
        h = whichProbing(h, person,m_table);
    } if (isEmpty(h, m_table)) {     //sets the first index or probed index
        m_table[h] = person;
        m_size++;
        //After every insertion we need to check for those criteria
        success = true;
        if (lambda() > 0.5 ){   //if the load factor becomes greater than 0.5,
            if (m_currentProb == LINEAR){
                setProbingPolicy(QUADRATIC);
            }else{
                setProbingPolicy(LINEAR);
            }
        }
    }
return success;
}

//helper to find which kind of probing that returns the index
int HashTable::whichProbing(int h, Person person, Person * hashTable){
    //we find out that the determined bucket is taken then go through probing algorithm
    //continue to probe while those conditions are not met
    //1 - the current index is occupied
    //2 - the current index does not hold the same value if the same value is found exit code
    int hash = h;
    int j = 0;
    if (m_currentProb == LINEAR){ //using the functions provided
        while (!isEmpty(h, hashTable) && hashTable[h].serial() != person.serial()) {
            j++;
            h = (hash + j) % m_capacity;   //begin probing
        }
    }else{
        j = 0;
        int squared;
        while (!isEmpty(h, hashTable) && hashTable[h].serial() != person.serial()) {
            squared = j * j;
            j++;
            h = ((hash % m_capacity) + squared) % m_capacity;   //begin probing
        }
    }
    return h;
}

//if the number of deleted buckets is more than 25 percent of the total number of occupied buckets
//we need to rehash to a new hash table and switch probing methods
//The capacity of the new table would be the smallest prime number greater than
bool HashTable::remove(Person person){
    //using whichProbing, it returns the index if found or the next empty if not found
   int h = m_hash(person.key()) % m_capacity;
    h = whichProbing(h, person, m_table);
    if(m_table[h] == person){   //check for equality
        m_table[h]= DELETED;    //mark deletedd
        m_numDeleted++;
        if (deletedRatio() > 0.25 ){   //if the deleted ratio is bigger than .25
            if (m_currentProb == LINEAR){
                setProbingPolicy(QUADRATIC);
            }else{
                setProbingPolicy(LINEAR);
            }
        }
        return true;
    }else{
        return false;
    }


}
//set given probing technique to m_currentProb
void HashTable::setProbingPolicy(probing prob){
    // create new table
    // the smallest prime number greater than 4 times the current number of data points.
    int dataPoints = 4 * (m_size - m_numDeleted);     //new m_capacity
    if (dataPoints < MINPRIME){
        dataPoints = MINPRIME;
    }else if (dataPoints > MAXPRIME){
        dataPoints = MAXPRIME;
    }else if (isPrime(dataPoints)){
        dataPoints = dataPoints;
    }else{
        dataPoints = findNextPrime(dataPoints);
    }

    Person * temp = new Person[dataPoints];  //create an array of persons
    for (int i = 0; i < dataPoints; i++) {  //set them to 0
        temp[i] = EMPTY;
    }
    int oldCapacity = m_capacity;
    m_capacity = dataPoints;
    m_currentProb = prob;
    m_size = 0;
    m_numDeleted = 0;

    int hash;
    for(int i = 0; i < oldCapacity; i++) {        //iterate throught the old array

        if (!(DELETED == m_table[i]) && !(isEmpty(i,m_table))) {     //ignore deleted or empty buckets
            //take the key from old and find h based on new capacity aka dataPoints
            //same process as insert but the person is in the old array
            hash = m_hash(m_table[i].key()) % m_capacity;
            if(!(isEmpty(hash,temp))){     //probing algorithm for first hash function is occupied
                hash = whichProbing(hash, m_table[i], temp);
           } if (isEmpty(hash,temp)) {     //sets the first index or probed index
               temp[hash].setKey(m_table[i].key());    //set up the new array of persons
               temp[hash].setSerial(m_table[i].serial());     //set up the new array of persons
               m_size++;                  //update new array size
           }

        }

    }


       delete [] m_table; //delete old array
       m_table = temp;  // new array is now being pointd by the object



}

float HashTable::lambda() const {
    return (float)m_size/(float)m_capacity;
}
//This function returns the ratio of the deleted buckets to the total number of occupied buckets .
float HashTable::deletedRatio() const {
    return (float)m_numDeleted/(float)m_size;
}

void HashTable::dump() const {
    for (int i = 0; i < m_capacity; i++) {
        cout << "[" << i << "] : " << m_table[i] << endl;
    }
}

bool HashTable::isPrime(int number){
    // If number is prime this function returns true
    // otherwise it returns false
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we won't go beyond MAXPRIME
    //the smallest prime would be next after MINPRIME
    if (current < MINPRIME) current = MINPRIME;
    for (int i=current; i<MAXPRIME; i++) {
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0)
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}