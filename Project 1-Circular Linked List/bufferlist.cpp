#include "bufferlist.h"
//constructor
BufferList::BufferList(int minBufCapacity){
    //case edge
    //minBuf < than 1
    if (minBufCapacity < 1){
        m_minBufCapacity = DEFAULT_MIN_CAPACITY;
    } else {
        m_minBufCapacity = minBufCapacity;   //the min size for circular buffers in the list
    }
    m_cursor = new Buffer(m_minBufCapacity);//m_cursor is a buffer
    m_cursor -> m_next = m_cursor;          //point m_next to head
    m_listSize = 1;                         //number of nodes in the list - always will have one
}

BufferList::~BufferList(){
    clear();
}

void BufferList::clear(){
    //This function deallocates all memory in the object.
    //Every BufferList object has pointers to Buffer objects,
    //then we also need to deallocate memory for the Buffer objects.
    //To clean a Buffer object we can call clear() function from Buffer.
    if (m_listSize > 0) { //list size is greater than 0
        for (int i = 0; i < m_listSize; i++) {
            Buffer *tempDelete = m_cursor->m_next; //create a temp node as the head pointer
            m_cursor->m_next = tempDelete->m_next;   //assign cursors pointer to new head
            tempDelete->clear();                     //delete buffer in buffer list
            delete tempDelete;                      //delete the buffer list it self
        }
    }

}

void BufferList::enqueue(const int& data) {

    try{
        m_cursor->enqueue(data);; //inserting data into queue if there is space
   }
    catch(overflow_error &e) {
        Buffer *toInsert;   //temp Buffer to insert
        if (( m_cursor->capacity() * INCREASE_FACTOR) <= (m_minBufCapacity * MAX_FACTOR)) { //is the array size less than max factor
            toInsert = new Buffer( m_cursor->capacity() * INCREASE_FACTOR); //create new buffer to hold info using prior capacity
        }
        else
            toInsert = new Buffer( m_minBufCapacity); //otherwise start from the min capacity for the array size

        toInsert->m_next = m_cursor->m_next;    //set new Node to point to head of linked list [newnode] -> [head] [...] [...] [cursor]
        m_cursor->m_next = toInsert;            //link end to the new buffer   [cursor]-> [newnode] -> [head] [...] [...]
        m_cursor = toInsert;                    //make cursor the new new inserted node
        m_listSize++;                           //spent an hour trying to figure out whats wrong, it was this line...
        m_cursor->enqueue(data);                //attempt to enqueue after creating a new Buffer in the list
    }
}

int BufferList::dequeue() {
    int tempNum;
    try{
        tempNum = (m_cursor->m_next->dequeue()); //deleting data from queue if not empty
    }
    catch(underflow_error &e) {
        if(m_cursor->empty())
            throw underflow_error("Last node and empty");
        Buffer *tempDelete = m_cursor->m_next; //create a temp node as the head pointer
        m_cursor->m_next = tempDelete->m_next;   //assign cursors pointer to new head
        tempDelete->clear();                     //delete buffer in buffer list
        delete tempDelete;                      //delete the buffer list it self
        m_listSize--;

        tempNum = (m_cursor->m_next->dequeue());           //delete from next buffer
    }
    return tempNum;
}

BufferList::BufferList(const BufferList & rhs){
    //must create a buffer with correct min capacity
    //must copy over information to the correct buffer capacity doesnt differ
    m_listSize = 1;
    m_minBufCapacity = rhs.m_minBufCapacity;    //match the same min capacity
    Buffer *toInsert = new Buffer(*rhs.m_cursor -> m_next); //create new buffer to hold info, if rhs is null there will still be a null Buffer created
    m_cursor = toInsert;                                    //copy information of buffer into list
    m_cursor -> m_next = m_cursor;                          //point first node to it self
    //this creates a new buffer in our list and fills it with rhs head info.
    //then points the only node in our list to it self as the head
    if (rhs.m_listSize >1) {
        toInsert = rhs.m_cursor->m_next->m_next;  //new node that has the Buffer value after head of cursor
        for (int i = 1; i < rhs.m_listSize; i++) {   //[1] [2][3]
            Buffer *copyBuff = new Buffer(*toInsert);
            copyBuff->m_next = m_cursor->m_next;    //set new Node to point to head of linked list [newnode] -> [head] [...] [...] [cursor]
            m_cursor->m_next = copyBuff;            //cursor end points to new node
            m_cursor = copyBuff;                    //make m_cursor the new ending
            m_listSize++;
            toInsert = toInsert->m_next;              //this will iterate through the list

        }
    }
}

const BufferList & BufferList::operator=(const BufferList & rhs){
    if (this != &rhs) { //prevent assigning object to it self
        this->clear();  //clear everything in the Object Buffer
        m_listSize = 1;
        m_minBufCapacity = rhs.m_minBufCapacity;    //match the same min capacity
        Buffer *toInsert = new Buffer(*rhs.m_cursor -> m_next); //create new buffer to hold info, if rhs is null there will still be a null Buffer created
        m_cursor = toInsert;                                    //copy information of buffer into list
        m_cursor -> m_next = m_cursor;                          //point first node to it self
        //this creates a new buffer in our list and fills it with rhs head info.
        //then points the only node in our list to it self as the head
        toInsert = rhs.m_cursor->m_next->m_next;  //new node that has the Buffer value after head of cursor

        for (int i =1; i < rhs.m_listSize; i++){   //[1] [2][3]
            Buffer *copyBuff = new Buffer(*toInsert);
            copyBuff->m_next = m_cursor->m_next;    //set new Node to point to head of linked list [newnode] -> [head] [...] [...] [cursor]
            m_cursor->m_next = copyBuff;            //cursor end points to new node
            m_cursor = copyBuff;                    //make m_cursor the new ending
            m_listSize++;
            toInsert = toInsert ->m_next;              //this will iterate through the list
        }
    }
    return *this;
}

void BufferList::dump(){
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}