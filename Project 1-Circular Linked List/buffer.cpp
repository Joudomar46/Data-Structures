#include "buffer.h"

Buffer::Buffer(int capacity){
    //allocates memory to an array of int(capacity)
    //no need to initialize m_next to null
    if (capacity < 1){              //Capacity < 1, capacity = 0 and no allocation
        m_capacity = 0;             //set capacity to 0
    } else {
        m_capacity = capacity;             //set capacity to intended capacity
        m_buffer = new int [capacity];     //pointer to dynamically allocated array
    }
    m_count = 0;          // current number of items in the buffer = 0
    m_start = 0;          // index of the first (oldest) item in the buffer = 0
    m_end = 0;            // index of the last (newest) item in the buffer
}

void Buffer::clear(){
    //This function deallocates all memory and
    // reinitialize all member variables.
    //test cases: 1- if anything is in array, 2- if array is empty
    if (m_capacity != 0) {    //if theres memory allocated
        delete[] m_buffer;
        m_capacity = 0;       //set capacity to intended capacity
        m_count = 0;          // current number of items in the buffer = 0
        m_start = 0;          // index of the first (oldest) item in the buffer = 0
        m_end = 0;            // index of the last (newest) item in the buffer
    } //otherwise do nothing
}

Buffer::~Buffer(){
    clear();
}

int Buffer::count(){return m_count;}

int Buffer::capacity(){return m_capacity;}

bool Buffer::full(){
    return (count() == capacity());  //since we are keeping track of how many
                                     // things are in array, if count = capacity then its full

}

bool Buffer::empty(){
    return (count() == 0);  //since we are keeping track of how many
                            // things are in array, if count = 0 then its empty
}

void Buffer::enqueue(int data) {
    //edge cases
    //if list is full
     if (full()) {      //throw exception if array is full
         throw overflow_error("enqueue the full queue!");
       }else {
           m_buffer[m_end] = data;              //insert data at the end
           m_end = (m_end + 1) % capacity();    //increment end
           m_count++;                           //increment count
       }

}

int Buffer::dequeue(){
    //edge cases
    //if list is empty
    if (empty())
        throw underflow_error("dequeue the empty queue!");
    else {
        int dataThrown = m_buffer[m_start];
        m_start = (m_start + 1) % capacity();
        m_count--;
        return dataThrown;
    }
}

//copy constructor
Buffer::Buffer(const Buffer & rhs){
    //edge cases
    //1. not correct capacity in array: meaning no data allocated
    //2. empty array: has capacity, no count in it, data allocated
    //3. more than one item in array
    if (rhs.m_capacity < 1){              //Capacity < 1, capacity = 0 and no allocation
        m_capacity = 0;             //set capacity to 0
        m_count = 0;          // current number of items in the buffer = 0
        m_start = 0;          // index of the first (oldest) item in the buffer = 0
        m_end = 0;            // index of the last (newest) item in the buffer
    } else {
        m_capacity = rhs.m_capacity; //copy size of rhs to new Object buffer
        m_buffer = new int[m_capacity];     //pointer to dynamically allocated array

        if (rhs.m_count > 0) {      //if there are data items inside
            m_count = rhs.m_count;
            m_start = rhs.m_start;
            m_end = rhs.m_end;
            for (int i = 0; i < rhs.m_capacity; i++) {
                // if (rhs.m_buffer[i] != nullptr) //making sure there is something in Object we want to copy
                m_buffer[i] = rhs.m_buffer[i]; //assign each variable to the correct/new address
            }
        }
        else {
            m_count = 0;          // current number of items in the buffer = 0
            m_start = 0;          // index of the first (oldest) item in the buffer = 0
            m_end = 0;            // index of the last (newest) item in the buffer

        }
    }

}

const Buffer & Buffer::operator=(const Buffer & rhs){
    //same edge cases as our copy constructor + self assignment
    if (this != &rhs) { //prevent assigning object to it self
        this->clear();  //clear everything in the Object Buffer
        if (rhs.m_capacity < 1){              //Capacity < 1, capacity = 0 and no allocation
            m_capacity = 0;             //set capacity to 0
            m_count = 0;          // current number of items in the buffer = 0
            m_start = 0;          // index of the first (oldest) item in the buffer = 0
            m_end = 0;            // index of the last (newest) item in the buffer
        } else {
            m_capacity = rhs.m_capacity; //copy size of rhs to new Object buffer
            m_buffer = new int[m_capacity];     //pointer to dynamically allocated array

            if (rhs.m_count > 0) {      //if there are data items inside
                m_count = rhs.m_count;
                m_start = rhs.m_start;
                m_end = rhs.m_end;
                for (int i = 0; i < rhs.m_capacity; i++) {
                    // if (rhs.m_buffer[i] != nullptr) //making sure there is something in Object we want to copy
                    m_buffer[i] = rhs.m_buffer[i]; //assign each variable to the correct/new address
                }
            }
            else {
                m_count = 0;          // current number of items in the buffer = 0
                m_start = 0;          // index of the first (oldest) item in the buffer = 0
                m_end = 0;            // index of the last (newest) item in the buffer

            }
        }
    }
    return *this;
}

void Buffer::dump(){
    int start = m_start;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}