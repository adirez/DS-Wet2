#include <iostream>
#include "MinHeap.h"

using std::cout;
using std::endl;

int main() {

    int arr[5];
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 5;
    arr[3] = 4;
    arr[4] = 7;

    MinHeap heap(5, arr);
    TrainingGroup** ptrArr = heap.makeHeap();
    TrainingGroup** ptrArr2 = new TrainingGroup*[6];
    for (int i=1; i<=5; ++i){
        ptrArr2 = ptrArr;
    }

    heap.decKey(5, -12);
    heap.insert(1);
    heap.insert(13);
    heap.insert(9);
    heap.decKey(3, 0);
    heap.insert(-20);
    heap.insert(-2);
    heap.insert(-10);


/*    for (int i = 0; i < 13; ++i) {
        cout << heap.getMin()->getID() << ", ";
        heap.delMin();
    }

    cout << endl;*/

    for (int i = 1; i <= 5 ; ++i) {
        cout << ptrArr2[i]->getIdx() << ", ";
    }

    cout << endl;

    return 0;
}