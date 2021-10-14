// CMSC 341 - Spring 2021 - Project 4
// person.cpp
// The implementation of the Class Person
#include "person.h"
Person::Person(string name, unsigned int serial) {
    m_name = name;
    m_serial = serial;
}
string Person::key() const {
    return m_name;
}
unsigned int Person::serial() const{
    return m_serial;
}
void Person::setKey(string key) {
    m_name = key;
}
void Person::setSerial(unsigned int serial) {
    m_serial = serial;
}
// Overloaded insertion operator.  Prints person's name (key),
// and vaccine serial number. This is a friend function in Person class.
ostream& operator<<(ostream& sout, const Person &person ) {
    if (!person.m_name.empty())
        sout << person.m_name << " (serial " << person.m_serial << ")";
    else
        sout << "";
    return sout;
}
// Overloaded equality operator. It returns true if two objects are equal.
// For testing inequality we can simply negate the return value of this operator.
bool operator==(const Person& lhs, const Person& rhs){
    return ((lhs.m_name == rhs.m_name) && (lhs.m_serial == rhs.m_serial));
}