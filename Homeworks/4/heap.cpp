
#include "heap.h"

Heap::~Heap(){delete [] _heap;}

bool Heap::enqueue(int key, int data){
    if (_heapSize > _numElements){
        Node aNode(key, data);
        _numElements++;
        _heap[_numElements] = aNode;
        upHeap(_numElements);
        return true;
    }
    else
        return false;
}
void Heap::upHeap(int anIndex){
    if(_ROOT_INDEX < anIndex){  //recursion check, seeing if parent index is less than testIndex
        if(_heap[anIndex/2].getKey() > _heap[anIndex].getKey()){ //parent key greater than testIndex
            Node temp = _heap[anIndex/2];                       //switch parent and child
            _heap[anIndex/2] = _heap[anIndex];
            _heap[anIndex]= temp;
            upHeap(anIndex/2); //recurse to the top and check the next parent of now switched index

        }
    }
}

Node Heap::dequeue(){
    Node temp;
    if (!empty()){
        temp = _heap[_ROOT_INDEX];
        _heap[_ROOT_INDEX] = _heap[_numElements];
        _numElements--;
        downHeap(_ROOT_INDEX);
    }
    return temp;
}
void Heap::downHeap(int anIndex){
    int left = anIndex*2; //the index of left child
    int right = anIndex*2+1; //index of right child
    int minChild = _numElements +1; //minChild chosen between right or left
    if(left <= _numElements){ //check to see if were at last node or only node
        if (left == _numElements)
        {minChild = left; } //assign right or left child as the minChild after comparing
        else minChild = (_heap[left]._key>=_heap[right]._key)? right:left;
    }
    if((minChild <= _numElements) && //take the minchild and check if its the last one
     (_heap[anIndex]._key > _heap[minChild]._key)){ //also check if parent is greater than minChild
        Node temp = _heap[minChild]; //if so switch them and go onto the newParent
        _heap[minChild] = _heap[anIndex];
        _heap[anIndex] = temp;
        downHeap(minChild);         //recursion to new parent
    }
}

















Node Heap::min(){
    return _heap[_ROOT_INDEX];
}
int Heap::size(){
    return _numElements;
}
bool Heap::empty(){
    return (_numElements == 0);
}
void Heap::inOrderTraversal(int anIndex){
    if (anIndex <= _numElements){
        cout << "(";
        inOrderTraversal(anIndex*2);//visit left
        cout << _heap[anIndex]._key << ":" << _heap[anIndex]._data; //visit node
        inOrderTraversal(anIndex*2+1);//visit right
        cout << ")";
    }
}
void Heap::dumpArray(){
    for(int i=_ROOT_INDEX; i<=_numElements; i++)
    {
        cout << "Element index" << i << ". key=" << _heap[i]._key <<
             "  data=" << _heap[i]._data << endl;
    }
}
void Heap::inOrderDump(){
    inOrderTraversal(_ROOT_INDEX);
}

ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getKey() << ":" << node.getData() << endl;
    return sout;
}