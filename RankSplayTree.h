//
// Created by adire on 31-Dec-17.
//

#ifndef WET2_RANKSPLAYTREE_H
#define WET2_RANKSPLAYTREE_H

#include "Exceptions.h"

/**
 * a generic class for a SplayTree, with a nested class for a node. the class holds a pointer to the root of the tree, to the minimum and maximum nodes
 * and an integer to hold the tree size.
 */
template<class T, class S>
class RankSplayTree {
private:

    /**
     * a nested class of the tree to represent a node in the tree. a node will hold a generic data, the sum of it's sub-tree's data, the key, the rank
     * and pointers to his sons and parent.
     */
    class Node {
    private:
        T *key;
        S *data;
        S *sumData;
        int rank;
        Node *parent;
        Node *right_son;
        Node *left_son;

        friend class RankSplayTree;

    public:
        /**
         * a constructor for a tree node.
         * @param key - the key of the node
         * @param data - the data of the node
         * @param parent - the parent under which the node will be listed as a son
         */
        Node(const T key, const S data, Node *parent);
        /**
         * a destructor for the node
         */
        ~Node();

        //operators to determine size of nodes. first compares the data value and then the key (a lower key means a bigger node)
        bool operator<(const Node &node) const;
        bool operator>(const Node &node) const;
    };

    Node *root;
    Node *min;
    Node *max;
    int size;

    //to make them unavailable to users (= delete does not work in g++)
    RankSplayTree &operator=(const RankSplayTree &rank_splay_tree);

    /**
     * splaying a node to the top of the tree to become a root. in the worst case scenario a node will be splayed through the entire height of the tree
     * which is averagely log(n) and thus splay will run in a complexity of log n
     * @param node - the node to splay
     */
    void splay(Node *node);
    /**
     * the types of splays (determined by the position and situation of the node to be splayed).
     * implemented as shown in the slides.
     * @param node - the node to be splayed
     */
    void zig(Node *node);
    void zigZag(Node *node);
    void zigZig(Node *node);
    /**
     * an aux function for inOrder that will receive a functor and perform it's action on any node by the sorting order. will run in O(n) since it runs
     * over 'n' nodes (not including the time of func itself)
     * @param cur_node - the root of the tree
     * @param func - the functor to perform on the nodes
     */
    template<class do_something>
    void inOrderAux(Node *cur_node, do_something &func);
    template<class do_something>
    // exactly similar to inOrderAux, only it will go in a reverse order. similarly, will run at O(n) (not considering the time of func)
    void inOrderAuxReverese(Node *cur_node, do_something &func);
    // an aux function for postOrderRemoval function. runs over 'n' nodes and thus run in a complexity of O(n)
    void postOrderAuxRemoval(Node *cur_node);
    // an aux function for 'isExist'. runs in an average complexity of log(n).
    Node *findAux(Node *cur_node, const T& key, const S &data);
    // joins two trees when the right tree is bigger than the left tree. runs at O(log n) since it runs to the bottom right of the left tree.
    void join(Node *left_tree, Node *right_tree);

    RankSplayTree(const RankSplayTree &rank_splay_tree);

public:
    // an empty constructor for the tree
    RankSplayTree();
    // destructor for the tree
    ~RankSplayTree();
    // isExist an object in the tree and returns it's pointer. calls findAux and runs in O(log n).
    T &find(const T &key, const S &data);
    // receives an object, sends it to 'isExist' to get the closest node and inserts it to the tree. after that, splays it to the root. runs in O(log n).
    void insert(const T &key, const S &data);
    // receives a key of an object to be removed from the tree. finds it, splays to the root, removes and calls 'join' to merge the trees. runs in O(log n).
    void remove(const T &key, const S &data);
    // receives a key and data of an object and calculates it's rank
    int getRank(const T &key, const S &data);
    // receives a key and data of an object and sums the data values of the entire sub-tree it is the root of.
    S getSumData(const T &key, const S &data);
    // receives an integer and returns the sum of the data values of the K best gladiators.
    S getBestK(int k);
    // returns the node which is the k-th node in the order
    Node *select(int k);
    Node *selectAux(int k, Node *node);
    // iterates through the nodes in order. calls inOrderAux and receives a func to perform on the nodes. runs in O(n) (for the iteration only).
    template<class do_something>
    void inOrder(do_something &func);
    // iterates through the nodes in reverse order. calls inOrderReverseAux and receives a func to perform on the nodes. runs in O(n) (iteration only).
    template<class do_something>
    void inOrderReverse(do_something &func);
    // returns the maximum object of the tree. runs in O(1) since the tree holds a pointer for the max.
    T &getMax();
    // returns the size (int) of the tree. runs in O(1) since the tree holds an integer for the size.
    int getSize();
};

/**
 * Public functions
 */

template<class T, class S>
RankSplayTree<T, S>::RankSplayTree() : root(NULL), min(NULL), max(NULL), size(0) {}

template<class T, class S>
RankSplayTree<T, S>::~RankSplayTree() {
    postOrderAuxRemoval(root);
}

template<class T, class S>
T &RankSplayTree<T, S>::find(const T &key, const S &data) {
    Node *found_node = findAux(root, key, data);
    splay(found_node);
    if (found_node == NULL || *found_node->key != key) {
        throw KeyNotFound();
    }
    return *found_node->key;
}

template<class T, class S>
void RankSplayTree<T, S>::insert(const T &key, const S &data) {
    Node *found_node = findAux(root, key, data);
    if (found_node != NULL && data == *found_node->data) {
        throw KeyAlreadyExists();
    }
    Node *to_insert = new Node(key, data, found_node);
    if (found_node != NULL) {
        if (*to_insert < *found_node) {
            found_node->left_son = to_insert;
        } else {
            found_node->right_son = to_insert;
        }
        to_insert->parent = found_node;
    }

    S *tmp_sum = to_insert->sumData;
    int tmp_rank = to_insert->rank;
    Node *tmp_node = to_insert;
    while (tmp_node->parent != NULL && tmp_node != root) {
        *tmp_node->parent->sumData += *tmp_sum;
        tmp_node->parent->rank += tmp_rank;
        tmp_node = tmp_node->parent;
    }

    splay(to_insert);
    if (found_node == NULL) {
        root = to_insert;
    }
    //updating min/max of the tree
    if (root->right_son == NULL) {
        max = root;
    }
    if (root->left_son == NULL) {
        min = root;
    }
    size++;
}

template<class T, class S>
void RankSplayTree<T, S>::remove(const T &key, const S &data) {
    if (root == NULL) {
        throw EmptyTree();
    }
    Node *found_node = findAux(root, key, data);
    if (key != *found_node->key) {
        throw KeyNotFound();
    }
    splay(found_node);
    Node *left_tree = root->left_son;
    Node *right_tree = root->right_son;
    delete root;
    size--;
    join(left_tree, right_tree);
}

template<class T, class S>
void RankSplayTree<T, S>::join(Node *left_tree, Node *right_tree){
    if(right_tree != NULL && left_tree != NULL){
        right_tree->parent = NULL;
        left_tree->parent = NULL;
        root = left_tree;
        Node *max_left = left_tree;
        while (max_left->right_son != NULL) {
            max_left = max_left->right_son;
        }
        splay(max_left);
        root->right_son = right_tree;
        root->parent = NULL;
        root->right_son->parent = root;
        *root->sumData += *root->right_son->sumData;
        root->rank += root->right_son->rank;
    } else if(right_tree == NULL && left_tree == NULL){
        root = NULL;
        max = NULL;
        min = NULL;
    } else if(right_tree == NULL){
        left_tree->parent = NULL;
        root = left_tree;
        Node *max_left = left_tree;
        while (max_left->right_son != NULL) {
            max_left = max_left->right_son;
        }
        splay(max_left);
        max = root;
        root->parent = NULL;
    } else {
        root = right_tree;
        root->parent = NULL;
        Node *min_right = right_tree;
        while (min_right->left_son != NULL) {
            min_right = min_right->left_son;
        }
        min = min_right;
    }
}

template<class T, class S>
template<class do_something>
void RankSplayTree<T, S>::inOrder(do_something &func) {
    inOrderAux(root, func);
}

template<class T, class S>
template<class do_something>
void RankSplayTree<T, S>::inOrderReverse(do_something &func) {
    inOrderAuxReverese(root, func);
}

template<class T, class S>
T &RankSplayTree<T, S>::getMax() {
    if (max == NULL) {
        throw EmptyTree();
    }
    return *max->key;
}

template<class T, class S>
int RankSplayTree<T, S>::getSize() {
    return size;
}

/**
 * private functions
 */

template<class T, class S>
void RankSplayTree<T, S>::splay(RankSplayTree::Node *node) {
    while (node!=NULL && node->parent != NULL && node != root && node->parent != root) {
        Node *p = node->parent;
        Node *g = p->parent;
        if ((*node < *p && *node > *g ) || (*node > *p && *node < *g)) {
            zigZag(node);
        } else {
            zigZig(node);
        }
    }
    if (node != NULL && node->parent != NULL && node->parent == root && node->parent != NULL) {
        zig(node);
    }
}

template<class T, class S>
void RankSplayTree<T, S>::zig(RankSplayTree::Node *node) {
    S tmp_root_sum = *root->sumData;
    S tmp_node_sum = *root->data;
    int tmp_root_rank = root->rank;
    int tmp_node_rank = 1;
    Node *tmp_root = root;
    if (root->left_son == node) {
        if (root->right_son != NULL) {
            tmp_node_sum += *root->right_son->sumData;
            tmp_node_rank += root->right_son->rank;
        }
        root->left_son = node->right_son;
        if (node->right_son != NULL) {
            tmp_node_sum += *node->right_son->sumData;
            tmp_node_rank += node->right_son->rank;
            root->left_son->parent = root;
        }
        node->right_son = root;

    } else {
        if (root->left_son != NULL) {
            tmp_node_sum += *root->left_son->sumData;
            tmp_node_rank += root->left_son->rank;
        }
        root->right_son = node->left_son;
        if (node->left_son != NULL) {
            tmp_node_sum += *node->left_son->sumData;
            tmp_node_rank += node->left_son->rank;
            root->right_son->parent = root;
        }
        node->left_son = root;
    }
    node->parent = NULL;
    root->parent = node;
    root = node;

    *root->sumData = tmp_root_sum;
    root->rank = tmp_root_rank;
    *tmp_root->sumData = tmp_node_sum;
    tmp_root->rank = tmp_node_rank;
}

template<class T, class S>
void RankSplayTree<T, S>::zigZag(RankSplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if (g == root) {
        root = node;
    }
    S new_n_sum = *g->sumData;
    S new_p_sum = *p->data;
    S new_g_sum = *g->data;
    int new_n_rank = g->rank;
    int new_p_rank = 1;
    int new_g_rank = 1;
    if (*node < *p) {
        if (p->right_son != NULL) { //W
            new_p_sum += *p->right_son->sumData;
            new_p_rank += p->right_son->rank;
        }
        if (g->left_son != NULL) { //X
            new_g_sum += *g->left_son->sumData;
            new_g_rank += g->left_son->rank;
        }
        //attach node's left son to g
        g->right_son = node->left_son;
        if (g->right_son != NULL) { //Y
            new_g_sum += *g->right_son->sumData;
            new_g_rank += g->right_son->rank;
            g->right_son->parent = g;
        }
        //attach nodes right son to p
        p->left_son = node->right_son;
        if (p->left_son != NULL) { //Z
            new_p_sum += *p->left_son->sumData;
            new_p_rank += p->left_son->rank;
            p->left_son->parent = p;
        }
        //attach both g and p to node
        node->left_son = g;
        node->right_son = p;
    } else {
        if (p->left_son != NULL) { //W
            new_p_sum += *p->left_son->sumData;
            new_p_rank += p->left_son->rank;
        }
        if (g->right_son != NULL) { //Z
            new_g_sum += *g->right_son->sumData;
            new_g_rank += g->right_son->rank;
        }
        //attach node's right son to g
        g->left_son = node->right_son;
        if (g->left_son != NULL) { //Y
            new_g_sum += *g->left_son->sumData;
            new_g_rank += g->left_son->rank;
            g->left_son->parent = g;
        }
        //attach nodes left son to p
        p->right_son = node->left_son;
        if (p->right_son != NULL) { //X
            new_p_sum += *p->right_son->sumData;
            new_p_rank += p->right_son->rank;
            p->right_son->parent = p;
        }
        //attach both g and p to node
        node->right_son = g;
        node->left_son = p;
    }
    node->parent = g->parent;
    if (g->parent != NULL && *g < *g->parent) {
        //g was a left son
        g->parent->left_son = node;
    } else if (g->parent != NULL) {
        g->parent->right_son = node;
    }
    p->parent = node;
    g->parent = node;

    *g->sumData = new_g_sum;
    *p->sumData = new_p_sum;
    *node->sumData = new_n_sum;
    g->rank = new_g_rank;
    p->rank = new_p_rank;
    node->rank = new_n_rank;
}

template<class T, class S>
void RankSplayTree<T, S>::zigZig(RankSplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if (g == root) {
        root = node;
    }
    S new_n_sum = *g->sumData;
    S new_p_sum = *p->data + *g->data;
    S new_g_sum = *g->data;
    int new_n_rank = g->rank;
    int new_p_rank = 2;
    int new_g_rank = 1;
    if (*node < *p) {
        if (g->right_son != NULL) { //Z
            new_p_sum += *g->right_son->sumData;
            new_g_sum += *g->right_son->sumData;
            new_p_rank += g->right_son->rank;
            new_g_rank += g->right_son->rank;
        }
        //attach p's right son to g
        g->left_son = p->right_son;
        if (g->left_son != NULL) { // Y
            new_p_sum += *g->left_son->sumData;
            new_g_sum += *g->left_son->sumData;
            new_p_rank += g->left_son->rank;
            new_g_rank += g->left_son->rank;
            g->left_son->parent = g;
        }
        //attach nodes right son to p
        p->left_son = node->right_son;
        if (p->left_son != NULL) { //X
            new_p_sum += *p->left_son->sumData;
            new_p_rank += p->left_son->rank;
            p->left_son->parent = p;
        }
        //attach p to node
        node->right_son = p;
        p->parent = node;
        //attach g to p
        p->right_son = g;
    } else {
        if (g->left_son != NULL) { //W
            new_p_sum += *g->left_son->sumData;
            new_g_sum += *g->left_son->sumData;
            new_p_rank += g->left_son->rank;
            new_g_rank += g->left_son->rank;
        }
        //attach p's left son to g
        g->right_son = p->left_son;
        if (g->right_son != NULL) { //X
            new_p_sum += *g->right_son->sumData;
            new_g_sum += *g->right_son->sumData;
            new_p_rank += g->right_son->rank;
            new_g_rank += g->right_son->rank;
            g->right_son->parent = g;
        }
        //attach nodes left son to p
        p->right_son = node->left_son;
        if (p->right_son != NULL) { //Y
            new_p_sum += *p->right_son->sumData;
            new_p_rank += p->right_son->rank;
            p->right_son->parent = p;
        }
        //attach p to node
        node->left_son = p;
        p->parent = node;
        //attach g to p
        p->left_son = g;
    }
    if (g->parent != NULL && *g < *g->parent) {
        //g was a left son
        g->parent->left_son = node;
    } else if (g->parent != NULL) {
        g->parent->right_son = node;
    }
    node->parent = g->parent;
    g->parent = p;

    *g->sumData = new_g_sum;
    *p->sumData = new_p_sum;
    *node->sumData = new_n_sum;
    g->rank = new_g_rank;
    p->rank = new_p_rank;
    node->rank = new_n_rank;
}

template<class T, class S>
template<class do_something>
void RankSplayTree<T, S>::inOrderAux(RankSplayTree::Node *cur_node, do_something &func) {
    if (cur_node == NULL) return;

    inOrderAux(cur_node->left_son, func);
    func(cur_node->data);
    inOrderAux(cur_node->right_son, func);
}

template<class T, class S>
template<class do_something>
void RankSplayTree<T, S>::inOrderAuxReverese(Node *cur_node, do_something &func) {
    if (cur_node == NULL) return;

    inOrderAuxReverese(cur_node->right_son, func);
    func(cur_node->data);
    inOrderAuxReverese(cur_node->left_son, func);
}

template<class T, class S>
void RankSplayTree<T, S>::postOrderAuxRemoval(RankSplayTree::Node *cur_node) {
    if (cur_node == NULL) return;
    postOrderAuxRemoval(cur_node->left_son);
    postOrderAuxRemoval(cur_node->right_son);
    delete cur_node;
}

template<class T, class S>
typename RankSplayTree<T, S>::Node *RankSplayTree<T, S>::findAux(RankSplayTree::Node *cur_node, const T& key, const S &data) {
    if (cur_node == NULL) return NULL;
    if (data == *cur_node->data) {
        return cur_node;
    }
    if (data > *cur_node->data) {
        if (cur_node->right_son == NULL) {
            return cur_node;
        }
        return findAux(cur_node->right_son, key, data);
    }
    if (data < *cur_node->data) {
        if (cur_node->left_son == NULL) {
            return cur_node;
        }
        return findAux(cur_node->left_son, key, data);
    }
    return  NULL;
}

template<class T, class S>
typename RankSplayTree<T, S>::Node *RankSplayTree<T, S>::select(int k) {
    if (k == 0) {
        return NULL;
    }
    return selectAux(k, root);
}

template<class T, class S>
typename RankSplayTree<T, S>::Node *RankSplayTree<T, S>::selectAux(int k, Node *node) {
    if ((node->left_son == NULL && k - 1 == 0) || (node->left_son != NULL && node->left_son->rank == k - 1)) {
        return node;
    } else if ((node->left_son == NULL && k -1 < 0) || (node->left_son != NULL && node->left_son->rank > k - 1)) {
        if (node->left_son == NULL) return NULL;
        return selectAux(k, node->left_son);
    }
    if (node->left_son == NULL) {
        return selectAux(k - 1, node->right_son);
    }
    return selectAux(k - node->left_son->rank - 1, node->right_son);
}

template<class T, class S>
int RankSplayTree<T, S>::getRank(const T &key, const S &data) {
    Node *node = findAux(root, key, data);
    if (node == NULL) {
        throw EmptyTree();
    } else if (key != *node->key) {
        throw KeyNotFound();
    }
    int rank = 0;
    Node *tmp_node = node;
    while (tmp_node != NULL) {
        if ((tmp_node == node || *tmp_node < *node) && tmp_node->left_son != NULL) {
            rank += tmp_node->left_son->rank;
            rank++;
        } else if (tmp_node == node || *tmp_node < *node) {
            rank++;
        }
        tmp_node = tmp_node->parent;
    }
    return rank;
}

template<class T, class S>
S RankSplayTree<T, S>::getSumData(const T &key, const S &data) {
    Node *node = findAux(root, key, data);
    if (node == NULL) {
        throw EmptyTree();
    } else if (key != *node->key) {
        throw KeyNotFound();
    }
    S totalScore = *node->data;
    if (node->left_son != NULL) {
        totalScore += *node->left_son->sumData;
    }
    Node *tmp_node = node->parent;
    while (tmp_node != NULL) {
        if (*tmp_node < *node && tmp_node->left_son != NULL) {
            totalScore += *tmp_node->left_son->sumData;
            totalScore += *tmp_node->data;
        } else if (*tmp_node < *node) {
            totalScore += *tmp_node->data;
        }
        tmp_node = tmp_node->parent;
    }
    return totalScore;
}

template<class T, class S>
S RankSplayTree<T, S>::getBestK(int k) {
    S totalScore = *root->sumData;
    Node *k_node = select(size - k);
    if (k_node == NULL) {
        return totalScore;
    }
    totalScore -= getSumData(*k_node->key, *k_node->data);

    return totalScore;
}

/**
 * Node functions
 */

template<class T, class S>
RankSplayTree<T, S>::Node::Node(const T key, const S data, Node *parent) : key(new T(key)), data(new S(data)), sumData(new S(data)),
                                                                           rank(1), parent(parent), right_son(NULL), left_son(NULL) {}

template<class T, class S>
RankSplayTree<T, S>::Node::~Node() {
    delete key;
    delete data;
    delete sumData;
}

template<class T, class S>
bool RankSplayTree<T, S>::Node::operator<(const RankSplayTree<T, S>::Node &node) const {
    return *this->data < *node.data || (*this->data == *node.data && *this->key > *node.key);
}

template<class T, class S>
bool RankSplayTree<T, S>::Node::operator>(const RankSplayTree<T, S>::Node &node) const {
    return *this->data > *node.data || (*this->data == *node.data && *this->key > *node.key);
}

#endif //WET2_RANKSPLAYTREE_H
