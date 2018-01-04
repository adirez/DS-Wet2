//
// Created by Shahak on 03/01/2018.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "Colosseum.h"
#include "List.h"
#include "TrainingGroup.h"
#include "RankSplayTree.h"

class HashTable {

    class HashNode {
    private:
        int groupID;
        bool conquered;
        TrainingGroup *groupHeapPtr;
        RankSplayTree<int, int> *gladRankSplayTree;

        friend class HashTable;

    public:
        HashNode(int id, TrainingGroup *ptr);
        HashNode(const HashNode& hashNode);
        ~HashNode();
    };

    List<HashNode*> *list;
    int size;
    int num_elem;

public:
    HashTable(int n, int* array, TrainingGroup** ptrArr);
    ~HashTable();
    bool isExist(int id);
    bool isConquered(int id);
    void insertGroup(int id, TrainingGroup* ptr);
    void insertGladiator(int id, int gladID, int gladScore);
    void setConquered(int id);
    TrainingGroup* getGroupHeapPtr(int id);
    RankSplayTree<int, int>* getGladTree(int id);
};

HashTable::HashTable(int n, int *array, TrainingGroup** ptrArr) {
    list = new List<HashNode*>[2*n];
    size = 2*n;
    int hash;
    for (int i = 0; i < n; ++i) {
        HashNode *hashNode = new HashNode(array[i], ptrArr[i+1]);
        hash = array[i] % size;
        list[hash].insert(hashNode);
    }
    num_elem = n;
}

HashTable::~HashTable() {
    delete list;
}

bool HashTable::isExist(int id) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode *hashNode = *it;
        if(hashNode->groupID == id){
            return true;
        }
    }
    return false;
}

bool HashTable::isConquered(int id) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode *hashNode = *it;
        if(hashNode->groupID == id){
            return hashNode->conquered;
        }
    }
    return false;
}

void HashTable::insertGroup(int id, TrainingGroup *ptr) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode *hashNode = *it;
        if(hashNode->groupID == id){
            throw KeyAlreadyExists();
        }
    }
    if(num_elem + 1 >= size){
        List<HashNode*> *list2 = new List<HashNode*>[2*size];
        size *= 2;
        for (int i = 0; i<= size/2; ++i){
            for (List<HashNode*>::Iterator it = list[i].begin(); it != list[i].end(); ++it) {
                HashNode *tempNode = new HashNode(**(it.cur_node->data));
                hash = tempNode->groupID % size;
                list2[hash].insert(tempNode);
            }
        }
        delete list;
        list = list2;
    }
    HashNode *hashNode = new HashNode(id, ptr);
    hash = id % size;
    list[hash].insert(hashNode);
    num_elem++;
}

void HashTable::insertGladiator(int id, int gladID, int gladScore) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it) {
        HashNode *hashNode = *it;
        hashNode->gladRankSplayTree->insert(gladID, gladScore);
    }
}

RankSplayTree<int, int> *HashTable::getGladTree(int id) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode *hashNode = *it;
        if(hashNode->groupID == id){
            return hashNode->gladRankSplayTree;
        }
    }
    return NULL;
}

void HashTable::setConquered(int id) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode *hashNode = *it;
        if(hashNode->groupID == id){
            hashNode->conquered = true;
        }
    }
}

TrainingGroup *HashTable::getGroupHeapPtr(int id) {
    int hash = id % size;
    for (List<HashNode*>::Iterator it = list[hash].begin(); it != list[hash].end(); ++it){
        HashNode *hashNode = *it;
        if(hashNode->groupID == id){
            return hashNode->groupHeapPtr;
        }
    }
    return NULL;
}

HashTable::HashNode::HashNode(int id, TrainingGroup *ptr) : groupID(id), conquered(false), groupHeapPtr(ptr) {
    gladRankSplayTree = new RankSplayTree<int, int>();
}

HashTable::HashNode::~HashNode() {
    delete gladRankSplayTree;
}

HashTable::HashNode::HashNode(const HashTable::HashNode &hashNode) : groupID(hashNode.groupID), conquered(hashNode.conquered),
                                                                     groupHeapPtr(hashNode.groupHeapPtr){
    delete gladRankSplayTree;
    gladRankSplayTree = hashNode.gladRankSplayTree;
}

#endif //WET2_HASHTABLE_H
