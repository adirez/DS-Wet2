//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "List.h"
#include "MinHeap.h"
#include "RankSplayTree.h"

class HashTable {

    class HashNode {
    private:
        int groupID;
        bool conquered;
        TrainingGroup *groupHeapPtr;
        RankSplayTree<int, int> *gladRankSplayTree;

        friend class HashTable;
        friend class Colosseum;

    public:
        HashNode(int id, TrainingGroup *ptr);
        HashNode(const HashNode& hashNode);
        ~HashNode();
    };

    List<HashNode*> *list;
    int size;
    int num_elem;

    friend class Colosseum;

public:
    HashTable(int n, int* array, TrainingGroup** ptrArr);
    ~HashTable();
    HashTable::HashNode* find(int id);
    void insertGroup(int id, TrainingGroup* ptr);
    void insertGladiator(HashNode *hashNode, int gladID, int gladScore);
};


#endif //WET2_HASHTABLE_H
