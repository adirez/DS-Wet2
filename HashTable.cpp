//
// Created by Shahak on 03/01/2018.
//

#include "HashTable.h"

class GroupsHashFunc {
public:
    int size;
    explicit GroupsHashFunc(int size) : size(size) {}
    int operator()(int group_id) {
        return group_id % size;
    }

    void updateSize(int n) {
        size = n;
    }
};

template <class S>
class GroupHashTable {
    HashTable<int,S,GroupsHashFunc> GroupHashTable;

};
