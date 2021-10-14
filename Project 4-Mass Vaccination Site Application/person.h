// CMSC 341 - Spring 2021 - Project 4
// person.h
// Simple class for use with HashTable class

// To work with HashTable, a class must provide the
// following:
//  (a) Default constructor, i.e. a constructor with default values
//  (b) key function (string key()), the key is the name of the person
//  (c) overloaded insertion operator
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;
using std::string;
using std::ostream;
class Person{
public:
    Person(string name="", unsigned int serial=0);
    string key() const;
    unsigned int serial() const;
    void setKey(string key);
    void setSerial(unsigned int serial);
    // Overloaded insertion operator
    friend ostream& operator<<(ostream& sout, const Person &person );
    // Overloaded equality operator
    friend bool operator==(const Person& lhs, const Person& rhs);
private:
    string m_name;
    unsigned int m_serial;
};
#endif