//
// Created by adire on 31-Dec-17.
//

#ifndef WET2_LIST_H
#define WET2_LIST_H

#include "Exceptions.h"

template <class T>
class List {
    class Node{
        T* data;
        Node *next;
        Node *previous;

        friend class List;
        friend class Iterator;
        friend class HashTable;
    public:
        Node(const T data);
        ~Node();
    };
    Node *head;
    Node *last;
    int size;

public:
    class Iterator{
        const List* list;
        Node *cur_node;
        Iterator(const List* list, Node *cur_node);

        friend class List;
        friend class HashTable;


    public:
        Iterator(const Iterator& it) : list(it.list), cur_node(it.cur_node) {};
        Iterator &operator=(const Iterator& it){
            if (this == &it){
                return *this;
            }
            list = it.list;
            cur_node = it.cur_node;
            return *this;
        }
        ~Iterator() {};
        T &operator*();
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        bool operator==(const Iterator iterator) const;
        bool operator!=(const Iterator iterator) const;
    };
    List();
    List(const List &list);
    ~List();
    List &operator=(const List &list);
    Iterator begin() const;
    Iterator end() const;
    void insert(T& data, Iterator iterator);
    void insert(T& data);
    void remove(Iterator iterator);
    bool operator==(const List& list) const;
    bool operator!=(const List& list) const;
    template <class Predicate>
    Iterator find(const Predicate& predicate) const;
    template <class Compare>
    void sort(const Compare& compare);
    int getSize() const;
};

/*--------------------------------------------------------------------------*//*
 *                          __    _      __
 *                         / /   (_)____/ /_
 *                        / /   / / ___/ __/
 *                       / /___/ (__  ) /_
 *                      /_____/_/____/\__/
 *
*//*--------------------------------------------------------------------------*/

template <class T>
List<T>::List() : head(NULL), last(NULL), size(0) {}

template <class T>
List<T>::List(const List &list) : head(NULL), last(NULL), size(0) {
    for (Iterator it = list.begin(); it != list.end(); ++it) {
        insert(*it.cur_node->data);
    }
}

template <class T>
List<T>::~List() {
    Iterator it = begin();
    while (it != end()){
        remove(it);
        it = begin();
    }
}

template <class T>
List<T> &List<T>::operator=(const List &list) {
    if (this == &list){
        return *this;
    }

    Iterator it_left = begin();
    while (it_left != end()){
        remove(it_left);
        it_left = begin();
    }

    for (Iterator it = list.begin(); it != list.end(); ++it) {
        insert(*it.cur_node->data);
    }
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(this, head);
}

template <class T>
typename List<T>::Iterator List<T>::end() const {
    return ++Iterator(this, last);
}

template <class T>
void List<T>::insert(T &data, Iterator iterator) {
    if(iterator.list != this){
        throw KeyNotFound();
    }
    Node *new_node = new Node(data);
    size++;
    if(size == 1){
        head = new_node;
        last = new_node;
        return;
    }
    Node *next_node = iterator.cur_node;
    if (next_node == NULL) {
        new_node->previous = last;
        new_node->next = last->next;
        last->next = new_node;
        last = new_node;
        return;
    }
    Node *prev_node = iterator.cur_node->previous;
    if (prev_node == NULL) {
        new_node->next = head;
        new_node->previous = NULL;
        head->previous = new_node;
        head = new_node;
        return;
    }
    new_node->next = next_node;
    new_node->previous = prev_node;
    next_node->previous = new_node;
    prev_node->next = new_node;
}

template <class T>
void List<T>::insert(T &data) {
    insert(data, end());
}

template <class T>
void List<T>::remove(Iterator iterator){
    if(iterator.list != this || iterator == end() || size == 0){
        throw KeyNotFound();
    }
    size--;
    if(size == 0){
        delete iterator.cur_node;
        head = NULL;
        last = NULL;
        return;
    }
    Node *prev_node = iterator.cur_node->previous;
    Node *next_node = iterator.cur_node->next;

    if (iterator.cur_node == head) {
        next_node->previous = NULL;
        delete iterator.cur_node;
        head = next_node;
        return;
    }
    if (iterator.cur_node == last) {
        prev_node->next = NULL;
        delete iterator.cur_node;
        last = prev_node;
        return;
    }
    next_node->previous = prev_node;
    prev_node->next = next_node;
    delete iterator.cur_node;
}

template <class T>
int List<T>::getSize() const{
    return size;
}

template <class T>
bool List<T>::operator==(const List &list) const {
    if (size != list.size){
        return false;
    }

    Iterator it_left = begin();
    Iterator it_right = list.begin();

    for ( ; it_left != end(); ++it_left, ++it_right) {
        if (*it_left.cur_node->data != *it_right.cur_node->data){
            return false;
        }
    }
    return true;
}

template <class T>
bool List<T>::operator!=(const List &list) const {
    return !(*this == list);
}

template <class T>
template <class Predicate>
typename List<T>::Iterator List<T>::find(const Predicate& predicate) const {
    Iterator it = begin();
    for( ; it != end(); ++it){
        if(predicate(*it) == true){
            break;
        }
    }
    return it;
}

template <class T>
template <class Compare>
void List<T>::sort(const Compare& compare) {
    for (Iterator i = begin(); i != end() ; ++i) {
        Iterator j = i;
        for (++j; j != end(); ++j) {
            if (!compare(*i.cur_node->data, *j.cur_node->data)){
                T* tmp = new T(*i.cur_node->data);
                delete i.cur_node->data;
                i.cur_node->data = new T(*j.cur_node->data);
                delete j.cur_node->data;
                j.cur_node->data = new T(*tmp);
                delete tmp;
            }
        }
    }
}

/*--------------------------------------------------------------------------*//*
 *                          _   __          __
 *                         / | / /___  ____/ /__
 *                        /  |/ / __ \/ __  / _ \
 *                       / /|  / /_/ / /_/ /  __/
 *                      /_/ |_/\____/\__,_/\___/
 *
*//*--------------------------------------------------------------------------*/

template <class T>
List<T>::Node::Node(T data) : data(new T(data)), next(NULL),
                                    previous(NULL) {}

template <class T>
List<T>::Node::~Node() {
    delete data;
}

/*--------------------------------------------------------------------------*//*
 *                       ____ __                   __
 *                      /  _// /____  _________  _/ /____  _____
 *                      / / / __/ _ \/ ___/ __ \/ __/ __ \/ ___/
 *                    _/ / / /_/  __/ /  / /_/ / /_/ /_/ / /
 *                   /___/ \__/\___/_/   \__,_/\__/\____/_/
 *
*//*--------------------------------------------------------------------------*/

template <class T>
List<T>::Iterator::Iterator(const List *list, List::Node *cur_node) :
        list(list),
        cur_node(cur_node) {}

template <class T>
T &List<T>::Iterator::operator*() {
    if (cur_node == NULL){
        throw KeyNotFound();
    }
    return *cur_node->data;
}

template <class T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
    if(this->cur_node == NULL){
        return *this;
    }
    cur_node = cur_node->next;
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator it = *this;
    ++*this;
    return it;
}

template <class T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
    if(cur_node == NULL){
        cur_node = list->last;
        return *this;
    }
    cur_node = cur_node->previous;
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator it = *this;
    --*this;
    return it;
}

template <class T>
bool List<T>::Iterator::operator==(const Iterator iterator) const {
    return list == iterator.list && cur_node == iterator.cur_node;
}

template <class T>
bool List<T>::Iterator::operator!=(const Iterator iterator) const {
    return !(*this == iterator);
}



#endif //WET2_LIST_H
