//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_COLOSSEUM_H
#define WET2_COLOSSEUM_H

#include "HashTable.h"

class Colosseum {
    MinHeap *minHeap;
    HashTable *hashTable;
    RankSplayTree<int, int> *rankSplayTree;
    RankSplayTree<int, int> *gladTree;

public:
    Colosseum(int n, int* trainingGroupsIDs);
    ~Colosseum();
    void addTrainingGroup(int trainingGroupID);
    void addGladiator(int gladiatorID, int score, int trainingGroup);
    void trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    int getMinTrainingGroup();
};


#endif //WET2_COLOSSEUM_H
