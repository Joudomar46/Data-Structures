// CMSC 341 - Spring 2021 - Project 3
// RQueue:

#ifndef _RQUEUE_H
#define _RQUEUE_H

#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;
using std::ostream;
using std::string;
using std::out_of_range;

class Grader;   // forward declaration (for grading purposes)
class Tester;   //forward declaration
class RQueue;   //forward declaration

// Constant parameters, min and max values
enum Year {YEAR4,YEAR3,YEAR2,YEAR1};
enum Major {CS,ENG,SCI};
enum Group {MINORITY,MAJORITY};
const int MINPRIO = 0;
const int MAXPRIO = 6;
//
// student class
//
class Student {
public:
    friend class Grader; // for grading purposes
    friend class Tester; // for testing purposes
    // Default constructor
    Student() {
        _name = ""; _priority = 6; _year = YEAR1; _major = SCI;_group = MAJORITY;
    }

    // Alternative constructor
    Student(string name, int priority, int year, int major, int group) {
        if ( (priority < MINPRIO || priority > MAXPRIO) || (year < YEAR4 || year > YEAR1) ||
             (major < CS || major > SCI) || (group < MINORITY || group > MAJORITY) )
            throw out_of_range("Bad value to Student constructor.");

        _name = name; _priority = priority; _year = year; _major = major; _group = group;
    }

    string getName() const {return _name;}
    int getPriority() const {return _priority;}
    int getYear() const {return _year;}
    int getMajor() const {return _major;}
    string getMajorStr() const{
        string result = "";
        switch (_major)
        {
            case CS:result = "CS";break;
            case ENG:result = "ENG";break;
            default:result = "SCI";break;
        }
        return result;
    }
    int getGroup() const {return _group;}
    string getGroupStr() const{
        string result = "";
        switch (_group)
        {
            case MINORITY:result = "Minority";break;
            default:result = "Majority";break;
        }
        return result;
    }
private:
    string _name;//student name
    int _priority;//0-6, this is a value specified by an officer
    int _year;//year in the school, for valid values refer to enum type Year
    int _major;//major studying, for valid values refer to enum type Major
    int _group;//status of being in minority group or not, refer to enum Group

};

class Node {
public:
    friend class Grader; // for grading purposes
    friend class Tester; // for testing purposes
    friend class RQueue; // RQueue has access to private memebers
    Node(Student student) {
        _student = student;
        _right = nullptr;
        _left = nullptr;
    }
    Student getStudent() const {return _student;}
private:
    Student _student;   // student information
    Node *_right;       // right child
    Node *_left;        // left child
};

// Overloaded insertion operators for Student and Node
ostream& operator<<(ostream& sout, const Student& student);
ostream& operator<<(ostream& sout, const Node& node);

// Priority function pointer type
typedef int (*prifn_t)(const Student&);

class RQueue {
public:

    friend class Grader; // for grading purposes
    friend class Tester; // for testing purposes

    // Constructor.  Create a queue with given priority function.
    RQueue(prifn_t priFn);

    // Destructor
    ~RQueue();

    // Copy constructor
    RQueue(const RQueue& rhs);

    // Assignment Operator
    RQueue& operator=(const RQueue& rhs);

    // Add a student to the queue
    void insertStudent(const Student& input);

    // Extract the highest priority student
    Student getNextStudent();

    // Merge two queues
    void mergeWithQueue(RQueue& rhs);

    // Remove all students from the queue
    void clear();

    // Return number of students in queue
    int numStudents() const;

    // Print the queue using preorder traversal. Although the first student
    // printed should have the highest priority, the remaining students will
    // not necessarily be in priority order.
    void printStudentQueue() const;

    // Get the current priority function.
    prifn_t getPriorityFn() const;

    // Set a new priority function.  Must rebuild the heap!!!
    void setPriorityFn(prifn_t priFn);

    // Dump the heap. For debugging purposes.
    void dump() const;

private:
    Node *_heap;       // Pointer to root of skew heap
    int _size;         // Current size of the heap
    prifn_t priority;  // Function pointer; function to compute priority

    // Private functions
    void dump(Node *pos) const;

    /******************************************
     * Private function declarations go here! *
     ******************************************/
    void recursivelyDelete(Node * node);
    Node* mergeHelper(Node *left, Node *right);


    void printStudentHelper(Node *node) const;

    void operatorHelper(Node *copy);
};
#endif