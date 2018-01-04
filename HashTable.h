//
// Created by Shahak on 03/01/2018.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include <cstdlib>
#include "List.h"

template <class T, class S, class do_something>
class HashTable {

private:

    class HashNode {
    private:
        T *key;
        S *data;

        friend class HashTable;

    public:
        HashNode(const T key, const S data) : key(key), data(data) {};
        ~HashNode();
    };

    List<HashNode*> *arr;
    do_something &func;
    int size;
    int used;

    int HashFunc(HashNode *node);

public:
    HashTable(int n, do_something &func);
    ~HashTable();
    void insert(T key, S data);
    void remove(T key, S data);

};

template <class T, class S, class do_something>
HashTable<T,S,do_something>::~HashTable() {
    for (int i = 0; i < size; ++i) {
        delete(arr[i]);
    }
    free(arr);
    delete(func);
}

template <class T, class S, class do_something>
HashTable<T,S,do_something>::HashTable(int n, do_something &func) : func(func) {
    size = 2 * n;
    arr = (List<HashNode*>*) malloc(2 * n * sizeof(List<HashNode*>));
    if (arr == NULL) {
        throw MemoryProblem();
    }
}

template <class T, class S, class do_something>
int HashTable<T,S,do_something>::HashFunc(HashNode *node) {
    return func(node);
};

template <class T, class S, class do_something>
void HashTable<T,S,do_something>::insert(T key, S data) {
    used++;
    if (used >= size) {
        size *= 2;
        List<HashNode*> *tmp_arr = (List<HashNode*>*)malloc(size * sizeof(List<HashNode*>));
        if (tmp_arr == NULL) {
            throw MemoryProblem();
        }
        for (int i = 0; i < size / 2; ++i) {

        }
    }
    HashNode *to_insert = new HashNode(key, data);
    int index = HashFunc(to_insert);
    arr[index].insert(to_insert);
}

template <class T, class S, class do_something>
void HashTable<T,S,do_something>::remove(T key, S data) {
    HashNode *to_insert = new HashNode(key, data);
    int index = HashFunc(to_insert);
    arr[index].insert(to_insert);
}

/**
 * Node functions
 */

template <class T, class S, class do_something>
HashTable<T,S,do_something>::HashNode::~HashNode() {
    delete key;
    delete data;
}

#endif //WET2_HASHTABLE_H
