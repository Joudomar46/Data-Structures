#include <iostream>
#include <string>
using namespace std;
class Heap;
class Node{
public:
    friend class Heap;
    Node():_key(0), _data(0){};
    Node(int key, int data):_key(key), _data(data){}
    Node& operator=(const Node& rhs){
        if ( this != &rhs ) {
            _key = rhs._key;
            _data = rhs._data;
        }
        return *this;
    }
    int getKey() const {return _key;}
    int getData() const {return _data;}
private:
    int _key;
    int _data;
};

class Heap{
public:
    Heap(int size = 100):_heapSize(size), _numElements(0){
        _heap = new Node[_heapSize];
        _ROOT_INDEX = 1;
    }
    ~Heap();
    bool enqueue(int key, int data);//this is the insert operation
    Node dequeue();//this is removeMin operation, it removes root
    void dumpArray();
    void inOrderDump();
    int size();
    bool empty();
    Node min();//this returns the root without removing it
private:
    void upHeap(int anIndex);
    void downHeap(int anIndex);
    void inOrderTraversal(int anIndex);
    Node* _heap;
    int _heapSize;
    int _numElements;
    int _ROOT_INDEX;
};

ostream& operator<<(ostream& sout, const Node& node);