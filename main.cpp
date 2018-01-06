//
// Created by adire on 06-Jan-18.
//

#include "MinHeap.h"

int main() {

    int arr[]={2,1};
    MinHeap minHeap(2, arr);
    minHeap.makeHeap();
    minHeap.insert(0);
    minHeap.decKey(3, -1);
    minHeap.delMin();
    minHeap.decKey(2, -1);
    minHeap.delMin();
    minHeap.insert(3);

    return 0;
}