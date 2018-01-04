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

    public:
        HashNode(int id, TrainingGroup *ptr);
        HashNode(const HashNode& hashNode);
        ~HashNode();
    };

    List<HashNode> *list;
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


#endif //WET2_HASHTABLE_H
