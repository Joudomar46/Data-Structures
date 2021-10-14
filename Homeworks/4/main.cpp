#include <iostream>
#include "heap.h"
using namespace std;
int main() {
    int array[]= {4,2,5,4,9};
    Heap aHeap(1001);
    for (int i=0; i<5;i++){
        aHeap.enqueue(array[i],array[i]*10);}

            cout << "In order dump: ";
            aHeap.inOrderDump();
            cout <<endl;
        aHeap.enqueue(1,10);
        cout << "In order dump: "; aHeap.inOrderDump();cout <<endl;
    aHeap.dequeue();
    cout << "In order dump: "; aHeap.inOrderDump();cout <<endl;



    return 0;
}
