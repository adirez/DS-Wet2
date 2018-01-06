//
// Created by adire on 04-Jan-18.
//

#include "HashTable.h"

HashTable::HashTable(int n, const int* array, TrainingGroup** ptrArr) {
    list = new List<HashNode>[2*n];
    size = 2*n;
    int hash = 0;
    for (int i = 0; i < n; ++i) {
        hash = array[i] % size;
        HashNode hashNode(array[i], ptrArr[i+1]);
        list[hash].insert(hashNode);
    }
    num_elem = n;
}

HashTable::~HashTable() {
    delete[] list;
}

void HashTable::insertGroup(int id, TrainingGroup *ptr) {
    int hash = id % size;
    for (List<HashNode>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode &hashNode = *it;
        if(hashNode.groupID == id){
            throw KeyAlreadyExists();
        }
    }
    if(num_elem + 1 >= size){
        List<HashNode> *list2 = new List<HashNode>[2*size];
        size *= 2;
        for (int i = 0; i < size/2; ++i){
            for (List<HashNode>::Iterator it = list[i].begin(); it != list[i].end(); ++it){
                HashNode &hashNode(*(it.cur_node->data));
                hash = hashNode.groupID % size;
                list2[hash].insert(hashNode);
            }
        }
        delete[] list;
        list = list2;
    }
    hash = id % size;
    HashNode hashNode(id, ptr);
    list[hash].insert(hashNode);
    num_elem++;
}

void HashTable::insertGladiator(HashNode &hashNode, int gladID, int gladScore) {
    hashNode.gladRankSplayTree->insert(gladID, gladScore);
}

HashTable::HashNode &HashTable::find(int id) {
    int hash = id % size;
    for (List<HashNode>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it) {
        if ((*it).groupID == -1){
            throw InvalidParameter();
        }
        if((*it).groupID == id){
            return *it;
        }
    }
    throw KeyNotFound();
}

HashTable::HashNode::HashNode(int id, TrainingGroup *ptr) : groupID(id), conquered(false), groupHeapPtr(ptr) {
    gladRankSplayTree = new RankSplayTree<int, int>();
}

HashTable::HashNode::~HashNode() {
    delete gladRankSplayTree;
}

HashTable::HashNode::HashNode(HashTable::HashNode &hashNode) : groupID(hashNode.groupID), conquered(hashNode.conquered),
                                                               groupHeapPtr(hashNode.groupHeapPtr){
    if(this == &hashNode){
        return;
    }
    gladRankSplayTree = hashNode.gladRankSplayTree;
    hashNode.gladRankSplayTree = NULL;
}