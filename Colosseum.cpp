//
// Created by adire on 04-Jan-18.
//

#include "Colosseum.h"

Colosseum::Colosseum(int n, int *trainingGroupsIDs) {
    rankSplayTree = new RankSplayTree<int, int>();
    gladTree = new RankSplayTree<int, int>();
    minHeap = new MinHeap(n, trainingGroupsIDs);
    TrainingGroup** ptrArr = minHeap->makeHeap();
    hashTable = new HashTable(n, trainingGroupsIDs, ptrArr);
}

void Colosseum::addTrainingGroup(int trainingGroupID) {
    hashTable->isExist(trainingGroupID);
    TrainingGroup* tempPtr = minHeap->insert(trainingGroupID);
    hashTable->insertGroup(trainingGroupID, tempPtr);
}

void Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {
    if(hashTable->isExist(trainingGroup)) throw KeyNotFound();
    gladTree->insert(gladiatorID, -1);
    hashTable->insertGladiator(trainingGroup, gladiatorID, score);
}

void Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2) {
    if(trainingGroup1 == trainingGroup2){
        throw InvalidParameter();
    }
    if(!hashTable->isExist(trainingGroup1) || !hashTable->isExist(trainingGroup2)) throw KeyNotFound();
    if(hashTable->isConquered(trainingGroup1) || hashTable->isConquered(trainingGroup2)) throw InvalidParameter();
    RankSplayTree<int, int> *gladTree1 = hashTable->getGladTree(trainingGroup1);
    RankSplayTree<int, int> *gladTree2 = hashTable->getGladTree(trainingGroup2);
    if(gladTree1->getBestK(k1) > gladTree2->getBestK(k2)){
        hashTable->setConquered(trainingGroup2);
        int heapIdx = hashTable->getGroupHeapPtr(trainingGroup2)->getIdx();
        minHeap->decKey(heapIdx, -1);
        minHeap->delMin();
    } else if(gladTree1->getBestK(k1) < gladTree2->getBestK(k2)){
        hashTable->setConquered(trainingGroup1);
        int heapIdx = hashTable->getGroupHeapPtr(trainingGroup1)->getIdx();
        minHeap->decKey(heapIdx, -1);
        minHeap->delMin();
    } else if(trainingGroup1 < trainingGroup2){
        hashTable->setConquered(trainingGroup2);
        int heapIdx = hashTable->getGroupHeapPtr(trainingGroup2)->getIdx();
        minHeap->decKey(heapIdx, -1);
        minHeap->delMin();
    } else {
        hashTable->setConquered(trainingGroup1);
        int heapIdx = hashTable->getGroupHeapPtr(trainingGroup1)->getIdx();
        minHeap->decKey(heapIdx, -1);
        minHeap->delMin();
    }

}

int Colosseum::getMinTrainingGroup() {
    return minHeap->getMin()->getID();
}

Colosseum::~Colosseum() {
    delete rankSplayTree;
    delete gladTree;
    delete hashTable;
    delete minHeap;
}