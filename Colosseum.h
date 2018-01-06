//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_COLOSSEUM_H
#define WET2_COLOSSEUM_H

#include "HashTable.h"

/**
 * the main structure of the data. hold a minimum heap to get the group with the minimal ID, a hash table for the groups to quickly access a group and
 * a rank splay tree to quickly access gladiators and calculate ranks and sums of scores.
 * the size complexity of the heap is O(m), the hash table O(m + n) and the tree O(m). therefore, a total of O(m + n).
 */
class Colosseum {
    MinHeap *minHeap;
    HashTable *hashTable;
    RankSplayTree<int, int> *gladTree;

public:
    /**
     * inits the system. receives an array of groups IDs and the size of the array. first, iterates through the array to check for valid values - O(n).
     * then, builds all of the structures:
     * the tree is built in O(1) since it's empty
     * the heap class is built in O(n) and then we call makeHeap which runs in O(n) as well
     * the hash table is created in O(n)
     * therefore, the function runs in O(n).
     * @param n - the size of the array
     * @param trainingGroupsIDs - the array of the groups IDs
     */
    Colosseum(int n, int* trainingGroupsIDs);
    /**
     * a destructor for the system. calls the destructor of the tree, hash table and heap.
     * the tree is destroyed in in O(m)
     * the hash table is destroyed in O(m + n)
     * the heap is destroyed in O(n)
     * therefore, the function runs in O(m + n)
     */
    ~Colosseum();
    /**
     *  receives an ID of a group and adds it to the system as an empty group. first, finds the group to see if it already exists. the 'find' function
     *  takes O(n) in the worst case and averagely on O(1). then, it's inserted to the heap which takes O(log n). finally, it's inserted to the hash
     *  table which takes O(log n). therefore, the function runs averagely in O(log n) and on the worst case in O(n).
     * @param trainingGroupID - the ID of the group to add
     */
    void addTrainingGroup(int trainingGroupID);
    /**
     * receives details of a gladiator and inserts it to the system. first, finds the group in the hash table which averagely takes O(1). then, it's
     * inserted to the gladiators tree which takes O(log m). finally, inserts it to the tree that belongs to the group in the hashtable which also takes
     * O(log m). therefore, the function runs in O(log m).
     * @param gladiatorID - the ID of the gladiator
     * @param score - the score of the gladiator
     * @param trainingGroup - the group the gladiator belongs to
     */
    void addGladiator(int gladiatorID, int score, int trainingGroup);
    /**
     *  receives IDs of two groups and two integers and takes the best gladiators of each group to fight against each other. first, find the groups in
     *  the hash table which averagely takes O(1). then, calls 'getBestK' for each of the groups' trees which takes O(log m). then, by the results it
     *  determines which group has won and marks the second group as lost. finally, the group that was marked as lost will be taken out of the heap using
     *  decKey and delMin which both run in O(log n). therefore, the function runs in a total complexity of O(log n + log m).
     * @param trainingGroup1 - ID of the first group
     * @param trainingGroup2 - ID of the second group
     * @param k1 - the number of warriors to take from the first group
     * @param k2 - the number of warriors to take from the second group
     */
    void trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);
    /**
     * returns the ID of the un-conquered group with the minimal ID. the heap removes any group which has been conquered and therefore we will simply
     * return the minimum of the heap in O(1).
     * @return - the ID of the minimal group
     */
    int getMinTrainingGroup();
};


#endif //WET2_COLOSSEUM_H
