//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "List.h"
#include "MinHeap.h"
#include "RankSplayTree.h"

/**
 * a class to hold the hash table by chain-hashing in a dynamic array. the hash function is modulu calculation of the array size. in addition, the
 * class holds as a member a tree of the gladiators IDs to find quickly whether or not an ID already exists and a rank-splay tree to hold the gladiators
 * in the group and calculate each gladiator's rank and sum of scores.
 * the table is is O(n) and the tree size is O(m) and thus the class takes O(m + n).
 */
class HashTable {

    /**
     * an inner class to hold a node in the linked list. each list of nodes is a member of the array and the groups are hashed into the relevant index
     * in the array.
     */
    class HashNode {
    private:
        int groupID;
        bool conquered;
        TrainingGroup *groupHeapPtr;
        RankSplayTree<int, int> *gladRankSplayTree;

        friend class HashTable;
        friend class Colosseum;

    public:
        /**
         * constructor for the node. receives a pointer for the group and an id and creates an empty tree, therefore runs in O(1)
         * @param id - the group's id
         * @param ptr - a pointer to the group
         */
        HashNode(int id, TrainingGroup *ptr);
        /**
         * a copy constructor for the node. moves the tree to the new node and runs in O(1).
         * @param hashNode - the node to copy
         */
        HashNode(HashNode& hashNode);
        /**
         * a destructor for the node. deletes the tree and runs in O(m) in the worst case.
         */
        ~HashNode();
    };

    List<HashNode> *list;
    int size;
    int num_elem;

    friend class Colosseum;

public:
    /**
     * a constructor for the hash table. allocates the array twice the size of 'n' and hashes the groups IDs into the arr using the hash funcion.
     * iterates through the entire array and thus runs in a time complexcity of O(n).
     * @param n - the size of the array
     * @param array - an array containing the IDs of the groups
     * @param ptrArr - an array of pointers to the groups
     */
    HashTable(int n, TrainingGroup** ptrArr);
    /**
     * a destructor for the hash table. deletes the array and all of the nodes within. the total sum of the gladiators within the entire table is m
     * and the number of the groups is O(n) and thus runs in a time complexity of O(m + n).
     */
    ~HashTable();
    /**
     * receives an id of a group and returns the node holding the group's details. first, hashes the given id to find the relevant index of the array
     * and then iterates through the list in the index to find the node. therefore, runs in a time complexity of the list length and thus in the worst
     * case it is the number of groups - O(n) and averagely on O(1).
     * @param id - the id of the group to be found
     * @return - the node containing the group's details
     */
    HashTable::HashNode &find(int id);
    /**
     * receives an id of a new group and it's pointer and inserts it to the hash table. first, hashes the id to find the relevant index and then checks
     * if the group ID already exists. if needed, a new list is created in the array or it is chained to the head of the list in the relevant index.
     * once the array is half full we'll re-allocate it and copy the lists to the new array. as we know, inserting a member to a hash table (including
     * a verification that the member does not already exist) and occasional increases of the size runs averagely on O(1).
     * @param id - the id of the new group
     * @param ptr - a pointer for the group
     */
    void insertGroup(int id, TrainingGroup* ptr);
    /**
     *  receives the node of the gladiator's group and the gladiator's details and inserts the gladiator to the group's tree of gladiators. therefore,
     *  runs in a time complexity of O(log m) according to the tree's insert function.
     * @param hashNode - the node of the group that the gladiator belongs to
     * @param gladID - the ID of the gladiator
     * @param gladScore - the score of the gladiator
     */
    void insertGladiator(HashNode &hashNode, int gladID, int gladScore);
};


#endif //WET2_HASHTABLE_H
