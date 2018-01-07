//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_MINHEAP_H
#define WET2_MINHEAP_H

#include "TrainingGroup.h"

/**
 * a class to hold a minimum heap of training groups pointers based on a dynamic array.
 * the array's size is O(n) and therefore the class's size is O(n).
 */
class MinHeap {
    TrainingGroup** arr;
    int size;
    int num_elem;

    void siftDown(int idx);
    void siftUp(int idx);
    void swap(int idx1, int idx2);

public:
    /**
     * a constructor for the minimum heap class. receives an array of the groups IDs and the number of groups and initializes the array in a size of
     * twice the number of groups. then, iterates through the array and allocates the groups within. therefore, time complexity is O(n).
     * @param n - the number of groups
     * @param array - the array of the groups IDs
     */
    MinHeap(int n, int* array);
    /**
     * a destructor for the minimum heap. iterates through the array and delete each training group and therefore runs in O(n) in the worst case.
     */
    ~MinHeap();
    /**
     * makes the heap - iterates over the first half of the array and sifts down. the array is build as an almost-full binary tree and therefore this
     * can be done in O(n).
     * @return - returns the array of the the groups in the heap to pass it for the hash c'tor
     */
    TrainingGroup** makeHeap();
    /**
     * receives a value of a training group and creates a new group to insert to the array. a group is created in O(1) and then inserted to the array.
     * insertion to a heap can be done in O(log n). if the array is now more than half full, we will re-allocate to a new array with double size and
     * copy the elements there which averagely takes O(1). therefore, the complexity is still O(log n).
     * @param value - the value of the group to be inserted
     * @return - a pointer to the created group
     */
    TrainingGroup* insert(int value);
    /**
     * receives a new (potentially lower) value to set for the group, changes it and sifts up. can be done in O(log n).
     * @param idx - the index of the group to be changed
     * @param value - the new value to set for the group
     */
    void decKey(int idx, int value);
    /**
     * returns the minimum of the heap which is at the first index of the array (1 in our case). runs in O(1).
     * @return - a pointer to the minimum group
     */
    TrainingGroup* getMin() const;
    /**
     * deletes the minimum from the array. the first member (the minimum) is swapped with the last member currently in the array and then deleted.
     * then, the first member (the one which was previously last) is sifted down which happens in O(log n). if the array is now less than quarter full,
     * we will re-allocate to a new array with half the size and copy the elements there which averagely takes O(1). therefore, the complexity is
     * still O(log n).
     */
    void delMin();
};


#endif //WET2_MINHEAP_H
