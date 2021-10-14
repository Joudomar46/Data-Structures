// CMSC 341 - Spring 2021 - Project 3
// RQueue:

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;


/************************
* This is the constructor for the RQueue class.
* It must be provided with a pointer to the prioritization function.
**********************/
RQueue::RQueue(prifn_t priFn)
{
    _heap = nullptr;  //set root to null
    _size = 0;        //size is at 0
    priority = priFn; //pointer to the prioritization function.
}
/************************
* destructor
* *********************/
RQueue::~RQueue()
{
    clear();  //clear function to help delete the nodes in the tree
    _heap = nullptr; //set the head of the tree to null
}
/************************
* copy constructor
* *********************/
RQueue::RQueue(const RQueue& rhs)
{
    if (this != &rhs) {        //prevent assigning object to it self
        this->_heap = nullptr;
        *this = rhs;            //call our assignment operator
    }
}

/************************
* assignment operator
* *********************/
RQueue& RQueue::operator=(const RQueue& rhs)
{
    if(this != &rhs){       //prevent assigning object to it self
        this->clear();      //deallocated memory if there is anything in this
        this->_heap = nullptr; //clear memory then set root to null
        this->_size = 0;        //reset the size
        this->priority = rhs.priority;  //set the priority so that the copying is correct
        operatorHelper(rhs._heap);
    }
    return *this;
}
/************************
* assignment operator helper to traverse the tree
* *********************/
void RQueue::operatorHelper(Node* copy){
    if (copy != nullptr){
        this->insertStudent(copy->_student);   //creates nodes and insert account info into function of new DTree
        operatorHelper(copy->_left);    //using preorder
        operatorHelper(copy->_right);
    }else return;
}

/************************
* Insert a Student into the queue.
* Must maintain the min-heap property.
* *********************/
void RQueue::insertStudent(const Student& input) {
    this->_heap = mergeHelper(this->_heap,new Node(input));     //set the new head of the tree with the help of merge function
    this->_size++;      //update size
}

/************************
* Extract (remove the node) and return the highest priority
* student from the queue. Must maintain the min-heap property.
* Should throw a domain_error exception if the queue is empty
* when the function is called.
* *********************/
Student RQueue::getNextStudent() {

    if (this->_heap != nullptr) {   //make sure queue is not empty or throw
        Node *oldRoot = _heap;      //temp variable to hold student info of priority aka top of tree
        this ->_heap = mergeHelper(_heap->_left, _heap->_right);    //call our lovely merge helper with the children of the root node
        Student tempStudent(oldRoot->_student);                     //get the student info of old root to return
        delete oldRoot;                                             //delete the node
        _size--;                                                    //update size
        return tempStudent;                                         //return the student
    }else
        throw domain_error("The queue is empty...can not delete");  //if queue is empty, catch in main

}



/************************
* Merge the host queue with the rhs; leaves rhs empty.
* Two skew heaps can only be merged if they have the same priority function.
* If the user attempts to merge queues with different priority functions,
* a domain_error exception should be thrown. This function requires protection
* against self-merging. Merging a heap with itself is not allowed.
* *********************/
void RQueue::mergeWithQueue(RQueue& rhs) {

    if (this->getPriorityFn() != rhs.getPriorityFn()) {  //throwing exception in this case
        throw domain_error("You are attempting to merge the queues with different priorities ");
    }
    if (this != &rhs) { //checking against self merging of queues
        this->_size = this->_size + rhs._size; //update size of merged array
        this->_heap = mergeHelper(this->_heap, rhs._heap); //pass in recursive function helper to merege

        //rhs needs to forget it self
        rhs._heap = nullptr;
        rhs._size = 0; //reset the size of the rhs queue
    }
}
/************************
* helper to merge using actual nodes and not trees object
* *********************/
Node* RQueue::mergeHelper(Node *left, Node *right){

    if(left == nullptr){return right;}  //checking null ptr cases
    else if(right == nullptr){return left;}
    else if(priority(left->_student) <= priority(right->_student)){
        Node * temp = left->_right;     //swap the two children
        left->_right = left->_left;
        left->_left = mergeHelper(right, temp);
        return left;
    }else
        return mergeHelper(right, left); //if the right child is priority

}

/************************
* clear for destructor
* *********************/
void RQueue::clear() {
    recursivelyDelete(_heap);
}

/************************
* helper to clear by traversing and deleting all the nodes
* *********************/
void RQueue::recursivelyDelete(Node *node) {
    if (node == nullptr) {
        return;}
    else{
        recursivelyDelete(node->_left);
        recursivelyDelete(node->_right);
        delete node;
    }

}

/************************
* Return the current number
* of students in the queue.
* *********************/
int RQueue::numStudents() const
{
    return _size; //size of queue is the same as how many elements (students) in queue
}

/************************
 * Print the contents of the queue using preorder traversal.
Although the first student printed should have the highest priority,
the remaining students will not necessarily be in priority order.
Please refer to the sample output file (driver.txt) for the format of
this function's output.
 * *********************/
void RQueue::printStudentQueue() const{
    if (_heap != nullptr) { //make sure there is something in the queue
        printStudentHelper(_heap);
    }else {
        cout << "The queue you want to print is empty."<<endl;
    }
}

/************************
* helper to traverse the tree
* *********************/
void RQueue::printStudentHelper(Node *node)const{
    if (node == nullptr)
        return;
    /* first print data of node */
    cout << "["<< priority(node->_student) << "] " << node->_student <<endl;
    printStudentHelper(node->_left);
    printStudentHelper(node->_right);
}

/************************
* Get the current priority function.
* *********************/
prifn_t RQueue::getPriorityFn() const {
    return priority; //returns priority variable
}

/************************
* Set a new priority function. It must rebuild the heap!
* get values from old heap and scrap the old one
* scrap the old one
* priority is calculated on the fly
* * *********************/
void RQueue::setPriorityFn(prifn_t priFn) {

    Student tempArray[this->_size]; //fill the array of students then reinsert them into the tree with new priority
    int sizeOfArray = this->_size;  //variable to hold the size of array before we change it

    for (int i = 0; i < sizeOfArray; i++) {     //array is being filled based on returned student from getNextStudent function
        tempArray[i] = (getNextStudent());
    }

    this->priority = priFn;                     //set the priority desired
    _heap = nullptr;                            //the root is set to null pointer

    for (int i = 0; i < sizeOfArray; i++) {     //inserting each element from the array using insertStudent
        this->insertStudent(*&tempArray[i]);
    }

}


// for debugging
void RQueue::dump() const
{
    if (_size == 0) {
        cout << "Empty skew heap.\n" ;
    } else {
        dump(_heap);
        cout << endl;
    }
}

// for debugging
void RQueue::dump(Node *pos) const {
    if ( pos != nullptr ) {
        cout << "(";
        dump(pos->_left);
        cout << priority(pos->_student) << ":" << pos->_student.getName();
        dump(pos->_right);
        cout << ")";
    }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
    sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
         << ", year: " << student.getYear() << ", major: " << student.getMajorStr()
         << ", group: " << student.getGroupStr();
    return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getStudent();
    return sout;
}