//
// Created by adire on 04-Jan-18.
//

#include <iostream>
#include "HashTable.h"

using std::cout;
using std::endl;

int main() {

    TrainingGroup** ptr;
    int arr[5];
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 5;
    arr[3] = 4;
    arr[4] = 7;

    HashTable hashTable(5, arr, ptr);

    return 0;
}