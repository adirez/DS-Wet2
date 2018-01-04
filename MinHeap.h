//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_MINHEAP_H
#define WET2_MINHEAP_H

#include "TrainingGroup.h"

class MinHeap {
    TrainingGroup** arr;
    int size;
    int num_elem;

    void siftDown(int idx);
    void siftUp(int idx);
    void swap(int idx1, int idx2);

public:
    MinHeap(int n, int* array);
    ~MinHeap();
    TrainingGroup** makeHeap();
    TrainingGroup* insert(int value);
    void decKey(int idx, int value);
    TrainingGroup* getMin() const;
    void delMin();
};


#endif //WET2_MINHEAP_H
