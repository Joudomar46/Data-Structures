#include "bufferlist.h"
#include <stdexcept>
#include <ctime>
class Tester{
public:
    bool BufferFullEmpty(int size);
    bool BufferEnqueueDequeue(Buffer &buffer, int dataCount);
    bool BufferEnqueueFull(int size);
    bool BufferDequeueEmpty(int size);
    bool BufferCopyConstructor( Buffer &buffer);
    bool BufferAssignOpper(Buffer &buffer);
    void BufListEnqueuePerformance(int numTrials, int N);
    bool BufferListEnqueueDequeue(BufferList &buffer, int dataCount);
    bool BufferListDequeueEmpty(int size);
    bool BufferListCopyConstructor( BufferList &buffer);
    bool BufferListAssignOpper( BufferList &buffer);
};
int main(){
    Tester tester;
    int bufferSize = 1000;
    Buffer buffer(bufferSize);
    {
        //testing full/empty
        cout << "\nTest case: Buffer class: Full and Empty:\n";
        if (tester.BufferFullEmpty(20))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for 1 data item
        cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
        if (tester.BufferEnqueueDequeue(buffer, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for half data size
        cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize/2))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for full data size
        cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
        if (tester.BufferEnqueueDequeue(buffer, bufferSize))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion in a full buffer
        cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
        if (tester.BufferEnqueueFull(1000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing deleting in a empty buffer
        cout << "\nTest case: Buffer class: Throwing exception while removing in empty buffer:\n";
        if (tester.BufferDequeueEmpty(1000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing copy in a empty buffer
        cout << "\nTest case: Buffer class: Copy an empty buffer:\n";
        if (tester.BufferCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing copy in a normal buffer, gets filled in function
        cout << "\nTest case: Buffer class: Copy a normal buffer:\n";
        if (tester.BufferCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing Buffer class copy constructor with buffer size less than zero
        cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
        Buffer buffer(-10);
        if (tester.BufferCopyConstructor(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing assignment copy in a normal buffer and empty buffer.
        cout << "\nTest case: Buffer class: assignment operator a normal buffer:\n";
        if (tester.BufferAssignOpper(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing Buffer class copy assignment constructor with buffer size less than zero
        cout << "\nTest case: Buffer class: assignment operator, negative buffer size:\n";
        Buffer buffer(-10);
        if (tester.BufferAssignOpper(buffer))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    BufferList buffList (100);
    {
        //testing insertion/removal for 1 data item
        cout << "\nTest case: Buffer List class: Inserting/removing 1 data item:\n";
        if (tester.BufferListEnqueueDequeue(buffList, 1))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for half data size
        cout << "\nTest case: Buffer List class: Inserting/removing half data size:\n";
        if (tester.BufferListEnqueueDequeue(buffList, 50))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing insertion/removal for a lot of data size
        cout << "\nTest case: Buffer List class: Inserting/removing a lot of data size:\n";
        if (tester.BufferListEnqueueDequeue(buffList, 10000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing deleting in a empty buffer list
        cout << "\nTest case: Buffer List class: Throwing exception while removing in empty buffer:\n";
        if (tester.BufferListDequeueEmpty(1000))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing copy in a empty buffer list
        cout << "\nTest case: Buffer List class: Copy an empty buffer:\n";
        if (tester.BufferListCopyConstructor(buffList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing copy in a normal buffer list
        cout << "\nTest case: Buffer List class: Copy an empty buffer:\n";
        for (int i = 0; i < 5000; i++)
            buffList.enqueue(i);
        if (tester.BufferListCopyConstructor(buffList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing copy in a negative buffer list
        cout << "\nTest case: Buffer List class: Copy an negative buffer:\n";
        BufferList buffList(-10);
        if (tester.BufferListCopyConstructor(buffList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing assignment operator in a empty buffer list
        cout << "\nTest case: Buffer List class: Copy an empty buffer:\n";
        if (tester.BufferListAssignOpper(buffList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing assignment operator in a normal buffer list
        cout << "\nTest case: Buffer List class: Copy an empty buffer:\n";
        for (int i = 0; i < 5000; i++)
            buffList.enqueue(i);
        if (tester.BufferListAssignOpper(buffList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //testing assignment operator in a normal buffer list
        cout << "\nTest case: Buffer List class: Copy an empty buffer:\n";
        BufferList buffList(-10);
        if (tester.BufferListAssignOpper(buffList))
            cout << "\tTest passed!\n";
        else
            cout << "\tTest failed!\n";
    }
    {
        //Measuring the efficiency of insertion functionality
        cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
        int M = 5;//number of trials
        int N = 100000;//original input size
        tester.BufListEnqueuePerformance(M, N);
    }
    {
    //an example of BufferList::dump()
    cout << "\nHere is an example of a linked list:" << endl;
    BufferList bufferList(5);
    for (int i=40;i>0;i--)
        bufferList.enqueue(i);
    bufferList.dump();
    }

    return 0;
}
bool Tester::BufferFullEmpty(int size){
    Buffer aBuffer(size);
        if (aBuffer.empty()) { //empty buffer
            for (int i = 0; i < size - 1; i++)  //fill except for last buffer position
                aBuffer.enqueue(i);
        }
        if (!aBuffer.full()) {         //if buffer is not full
            aBuffer.enqueue(8675309);    // add another data member to make it true
        }
        if (aBuffer.full()){          //now it should be full so the test is complete
            return true;
    }
        return false;
}

bool Tester::BufferEnqueueDequeue(Buffer &buffer, int dataCount){

    for (int i=0;i<dataCount;i++)   //fill in the dataCount using loop, will work for all
        buffer.enqueue(i);
    for (int i=0;i<dataCount;i++)   //half data inserted or full data inserted/ removed
        buffer.dequeue();
    if(buffer.empty()){             //since we fill in and remove the same amount of data,
        return true;                //if buffer is empty then everything was properly deleted
    }else
        return false;
}
bool Tester::BufferEnqueueFull(int size){
    Buffer aBuffer(size);
    for (int i=0;i<size;i++)
        aBuffer.enqueue(i);
    try{
        //trying to insert in a full buffer
        aBuffer.enqueue(size+1);
    }
    catch(overflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}
bool Tester::BufferDequeueEmpty(int size){
    Buffer aBuffer(size);
    for (int i=0;i<size;i++)    //fill in buffer
        aBuffer.enqueue(i);

    for (int i=0;i<size;i++)    //remove the full buffer
        aBuffer.dequeue();
    try{
        //trying to insert in a empty buffer
        aBuffer.dequeue();
    }
    catch(underflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}
bool Tester::BufferCopyConstructor(Buffer &buffer){
    Buffer aBuffer(buffer);     //copy buffer into aBuffer
    //to check for deep copy check memory addresses
    //see if the the Buffers are separate entities
    for (int i = 0; i < buffer.capacity(); i++) { //this checks a buffer with capacity but no values
        if (&buffer.m_buffer[i] == &aBuffer.m_buffer[i]) {    //check each index
            return false;                   //if at any point this is not true
        }
    }
    for (int i=0;i<buffer.capacity();i++) //fill the buffer copy
        aBuffer.enqueue(i);
    Buffer anBuffer(buffer);              //testing when a buffer has capacity and values in array
    for (int i = 0; i < buffer.capacity(); i++) {
        if (&buffer.m_buffer[i] == &aBuffer.m_buffer[i]) {    //check each index
            return false;                   //if at any point this is not true
        }
    }
        return true;
}
bool Tester::BufferListEnqueueDequeue(BufferList &buffer, int dataCount){
    for (int i=0;i<dataCount;i++)   //fill in the dataCount using loop, will work for all
        buffer.enqueue(i);
    for (int i=0;i<dataCount;i++)   //half data inserted or full data inserted/ removed
        buffer.dequeue();
    if(buffer.m_listSize == 1){      //since we fill in and remove the same amount of data
        return true;                //if buffer has one left then everything was properly deleted
    }else
        return false;
}
bool Tester::BufferListDequeueEmpty(int size){
    BufferList aBuffer(size);
    for (int i=0;i<size;i++)    //fill in buffer
        aBuffer.enqueue(i);

    for (int i=0;i<size;i++)    //remove the full buffer
        aBuffer.dequeue();
    try{
        //trying to insert in a empty buffer
        aBuffer.dequeue();
    }
    catch(underflow_error &e){
        //the exception that we expect
        return true;
    }
    catch(...){
        //any other exception, this case is not acceptable
        return false;
    }
    //no exception thrown, this case is not acceptable
    return false;
}

bool Tester::BufferListCopyConstructor(BufferList &buffer){
    BufferList aBuffer(buffer);     //copy buffer into aBuffer
    //to check for deep copy check memory addresses
    //see if the the Buffers are separate entities
    Buffer* temp = buffer.m_cursor->m_next;
    Buffer* temp2 = aBuffer.m_cursor->m_next;
    for(int i=0;i < buffer.m_listSize;i++){
        for (int i = 0; i < temp->capacity(); i++) {
            if (&temp[i] == &temp2[i]) {    //check each index address
                return false;                   //if at any point this is not true
            }
        }
        temp = temp->m_next;
        temp2 = temp2->m_next;
    }

    return true;
}
bool Tester::BufferListAssignOpper(BufferList &buffer){
    BufferList aBuffer = buffer;     //copy buffer into aBuffer
    //to check for deep copy check memory addresses
    //see if the the Buffers are separate entities
    Buffer* temp = buffer.m_cursor->m_next;
    Buffer* temp2 = aBuffer.m_cursor->m_next;
    for(int i=0;i < buffer.m_listSize;i++){
        for (int i = 0; i < temp->capacity(); i++) {
            if (&temp[i] == &temp2[i]) {    //check each index
                return false;                   //if at any point this is not true
            }
        }
        temp = temp->m_next;
        temp2 = temp2->m_next;
    }
    return true;
}
void Tester::BufListEnqueuePerformance(int numTrials, int N){
    const int a = 2;//scaling factor for input size
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k=0;k<numTrials-1;k++)
    {
        BufferList p1(N);//the algorithm to be analyzed for efficiency
        start = clock();
        for(int i=0; i < N;i++){
            p1.enqueue(i);
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Inserting " << N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
        N = N * a;//increase the input size by the scaling factor
    }
}
bool Tester::BufferAssignOpper(Buffer &buffer){
    Buffer aBuffer = buffer;     //copy buffer into aBuffer
    //to check for deep copy check memory addresses
    //see if the the Buffers are separate entities
    for (int i = 0; i < buffer.capacity(); i++) { //this checks a buffer with capacity but no values
        if (&buffer.m_buffer[i] == &aBuffer.m_buffer[i]) {    //check each index
            return false;                   //if at any point this is not true
        }
    }
    for (int i=0;i<buffer.capacity();i++) //fill the buffer copy again
        aBuffer.enqueue(i);
    Buffer anBuffer = buffer;              //testing when a buffer has capacity and values in array
    for (int i = 0; i < buffer.capacity(); i++) {
        if (&buffer.m_buffer[i] == &aBuffer.m_buffer[i]) {    //check each index
            return false;                   //if at any point this is not true
        }
    }
    return true;

}