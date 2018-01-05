#include <iostream>
#include "Colosseum.h"

using std::cout;
using std::endl;

int main() {

    int arr[3];
    arr[0] = 1;
    arr[1] = 3;
    arr[2] = 5;

    MinHeap minHeap(3, arr);
    minHeap.insert(0);
    minHeap.decKey(1, -1);
    minHeap.delMin();
    minHeap.decKey(3, -1);
    minHeap.delMin();

    return 0;
}