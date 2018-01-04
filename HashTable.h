//
// Created by Shahak on 03/01/2018.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include <cstdlib>
#include "List.h"

template <class T>
class HashTable {

private:

    class HashNode {
    private:
        int key;
        T *data;

        friend class HashTable;

    public:
        HashNode(const int key, const T data) : key(key), data(data) {};
        ~HashNode();
    };

    List<HashNode*> *arr;
    int size;
    int used;

    int HashFunc(int key);

public:
    explicit HashTable(int n);
    ~HashTable();
    void insert(int key, T data);
    void remove(int key, T data);
    List<HashNode*>::Node *find(int key) {

    };

template <class T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < size; ++i) {
        delete(arr[i]);
    }
    free(arr);
}

template <class T>
HashTable<T>::HashTable(int n) {
    used = 0;
    size = 2 * n;
    if (n == 0) {
        size = 1; // so we can always insert a node
    }
    arr = (List<HashNode*>*) malloc(size * sizeof(List<HashNode*>));
    if (arr == NULL) {
        throw MemoryProblem();
    }
}

template <class T>
int HashTable<T>::HashFunc(int key) {
    return key % size;
};

template <class T>
void HashTable<T>::insert(int key, T data) {
    used++;
    if (arr[HashFunc(key)] == NULL) {
        arr[HashFunc(key)] = new List<HashNode*>;
    }
    arr[HashFunc(key)].insert(data);

    if (used >= size) {
        size *= 2;
        List<HashNode*> *tmp_arr = (List<HashNode*>*)malloc(size * sizeof(List<HashNode*>));
        if (tmp_arr == NULL) {
            throw MemoryProblem();
        }
        for (int i = 0; i < size / 2; ++i) {
            for (List<HashNode*>::Iterator it = arr[i].begin(); it != arr[i].end(); ++it) {
                tmp_arr[HashFunc(it->cur_node->data)].insert(it.cur_node->data);
                delete(arr[HashFunc(it.cur_node->data)]);
            }
            delete(arr[i]);
        }
        free(arr);
        arr = tmp_arr;
    }
}

template <class T>
void HashTable<T>::remove(int key, T data) {
    List<HashNode*>::Node *found_node = find(key);
    if (found_node == NULL) {
        throw KeyNotFound();
    }
    List<HashNode *>::Iterator it = arr[HashFunc(key)].find(key);
    arr[HashFunc(key)].remove(it);

    if (arr[HashFunc(key)].getSize() == 0) {
        delete(arr[HashFunc(key)]);
    }

    used--;
    if (used < (size / 2)) {
        size /= 2;
        List<HashNode*> *tmp_arr = (List<HashNode*>*)malloc(size * sizeof(List<HashNode*>));
        if (tmp_arr == NULL) {
            throw MemoryProblem();
        }
        for (int i = 0; i < size / 2; ++i) {
            for (List<HashNode*>::Iterator it = arr[i].begin(); it != arr[i].end(); ++it) {
                tmp_arr[HashFunc(it->cur_node->data)].insert(it.cur_node->data);
                delete(arr[HashFunc(it.cur_node->data)]);
            }
            delete(arr[i]);
        }
        free(arr);
        arr = tmp_arr;
    }
}

template <class T>
List<HashNode*>::Node *HashTable<T>::find(int key) {
    int index = HashFunc(key);
    for (List<HashNode*>::Iterator it = arr[index].begin(); it != arr[index].end(); ++it) {
        if (it.cur_node->data == key) {
            return it.cur_node;
        }
    }
    return NULL;
}

/**
 * Node functions
 */

template <class T>
HashTable<T>::HashNode::~HashNode() {
    delete data;
}

#endif //WET2_HASHTABLE_H
