//
// Created by adire on 04-Jan-18.
//

#include "Colosseum.h"

Colosseum::Colosseum(int n, int *trainingGroupsIDs) {
    gladTree = new RankSplayTree<int, int>();
    minHeap = new MinHeap(n, trainingGroupsIDs);
    TrainingGroup** ptrArr = minHeap->makeHeap();
    hashTable = new HashTable(n, trainingGroupsIDs, ptrArr);
}

void Colosseum::addTrainingGroup(int trainingGroupID) {
    HashTable::HashNode* hashNode = hashTable->find(trainingGroupID);
    if(hashNode != NULL) throw KeyAlreadyExists();
    TrainingGroup* tempPtr = minHeap->insert(trainingGroupID);
    hashTable->insertGroup(trainingGroupID, tempPtr);
}

void Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup) {
    HashTable::HashNode* hashNode = hashTable->find(trainingGroup);
    if(hashNode == NULL) throw KeyNotFound();
    gladTree->insert(gladiatorID, -1);
    hashTable->insertGladiator(hashNode, gladiatorID, score);
}

void Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2) {
    if(trainingGroup1 == trainingGroup2){
        throw InvalidParameter();
    }
    HashTable::HashNode* hashNode1 = hashTable->find(trainingGroup1);
    HashTable::HashNode* hashNode2 = hashTable->find(trainingGroup2);
    if(hashNode1 == NULL || hashNode2 == NULL) throw KeyNotFound();
    if(hashNode1->conquered || hashNode2->conquered) throw InvalidParameter();
    int bestK1, bestK2;
    bestK1 = hashNode1->gladRankSplayTree->getBestK(k1);
    bestK2 = hashNode2->gladRankSplayTree->getBestK(k2);
    if((bestK1 == bestK2 && trainingGroup1 < trainingGroup2) || bestK1 > bestK2){
        hashNode2->conquered = true;
        int heapIdx = hashNode2->groupHeapPtr->getIdx();
        minHeap->decKey(heapIdx, -1);
        minHeap->delMin();
    } else if((bestK1 == bestK2 && trainingGroup1 > trainingGroup2) || bestK1 < bestK2){
        hashNode1->conquered = true;
        int heapIdx = hashNode1->groupHeapPtr->getIdx();
        minHeap->decKey(heapIdx, -1);
        minHeap->delMin();
    }

}

int Colosseum::getMinTrainingGroup() {
    return minHeap->getMin()->getID();
}

Colosseum::~Colosseum() {
    delete gladTree;
    delete hashTable;
    delete minHeap;
}