//
// Created by adire on 04-Jan-18.
//

#include <cstdlib>
#include "MinHeap.h"

MinHeap::MinHeap(int n, int *array) {
    arr = new TrainingGroup*[2*n];
    for (int i = 1; i <= n; ++i) {
        arr[i] = new TrainingGroup(array[i-1], i);
    }
    size = 2*n;
    num_elem = n;
}

MinHeap::~MinHeap() {
    for (int i = 1; i <= num_elem; ++i) {
        TrainingGroup *to_delete = arr[i];
        delete to_delete;
    }
    delete[] arr;
}

void MinHeap::makeHeap() {
    for (int i = num_elem/2; i >= 1; --i) {
        siftDown(i);
    }
}

void MinHeap::siftDown(int idx) {
    while (2 * idx <= num_elem) {
        if (2 * idx == num_elem) { //idx has only one child
            if (*arr[idx] > *arr[idx * 2]) {
                swap(idx, idx * 2);
            }
            return;
        } else { //idx has 2 children
            if (*arr[idx] > *arr[idx * 2] && *arr[idx * 2] <= *arr[(idx * 2) + 1]) {
                swap(idx, idx * 2);
                idx *= 2;
            } else if (*arr[idx] > *arr[idx * 2 + 1] && *arr[idx * 2 + 1] <= *arr[idx * 2]) {
                swap(idx, idx * 2 + 1);
                idx = idx * 2 + 1;
            } else {
                return;
            }
        }
    }
}

void MinHeap::siftUp(int idx) {
    while (idx >= 2 && *arr[idx] < *arr[idx / 2]) {
        swap(idx, idx / 2);
        idx /= 2;
    }
}

TrainingGroup* MinHeap::insert(int value) {
    if (num_elem + 1 >= size) {
        TrainingGroup** arr2 = new TrainingGroup*[2*size];
        for (int i = 1; i <= num_elem; ++i) {
            arr2[i] = arr[i];
            arr[i] = NULL;
        }
        TrainingGroup** to_delete = arr;
        delete[] to_delete;
        arr = arr2;
        size *= 2;
    }
    TrainingGroup* elem = new TrainingGroup(value, num_elem + 1);
    arr[num_elem + 1] = elem;
    num_elem++;
    siftUp(num_elem);
    return elem;
}

void MinHeap::decKey(int idx, int value) {
    if(value >= arr[idx]->getID()) return;
    arr[idx]->setID(value);
    siftUp(idx);
}

TrainingGroup* MinHeap::getMin() const {
    if(num_elem == 0) return NULL;
    return arr[1];
}

void MinHeap::delMin() {
    if (num_elem == 0) throw EmptyHeap();
    if (num_elem == 1){
        TrainingGroup *to_delete = arr[1];
        delete to_delete;
        num_elem--;
        return;
    }
    swap(1, num_elem);
    TrainingGroup *to_delete = arr[num_elem];
    delete to_delete;
    num_elem--;
    siftDown(1);
    if(num_elem <= size /4){
        TrainingGroup** arr2 = new TrainingGroup*[size /2];
        for (int i = 1; i <= num_elem; ++i) {
            arr2[i] = arr[i];
            arr[i] = NULL;
        }
        TrainingGroup** to_delete_arr = arr;
        delete[] to_delete_arr;
        arr = arr2;
        size /= 2;
    }
}

void MinHeap::swap(int idx1, int idx2) {
    TrainingGroup* temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;

    int temp_idx = arr[idx1]->getIdx();
    arr[idx1]->setIdx(arr[idx2]->getIdx());
    arr[idx2]->setIdx(temp_idx);
}

TrainingGroup **MinHeap::getArr() {
    return arr;
}
