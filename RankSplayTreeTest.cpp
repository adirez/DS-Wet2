//
// Created by Shahak on 03/01/2018.
//

#include "RankSplayTree.h"
#include <iostream>

int main() {

    RankSplayTree<int, int> *Tree = new RankSplayTree<int, int>();
    Tree->insert(1,1);
    Tree->insert(2,2);
    Tree->insert(7,7);
    Tree->insert(20,20);
    Tree->insert(5,5);
    Tree->insert(13,13);
    Tree->insert(9,9);
    Tree->insert(0,0);
    Tree->insert(6,6);
    Tree->insert(30,30);
    Tree->remove(20,20);
    Tree->remove(0,0);
    Tree->remove(2,2);
    Tree->remove(5,5);
    Tree->remove(1,1);
    Tree->remove(7,7);
    Tree->remove(13,13);
    Tree->remove(9,9);
    Tree->remove(30,30);
    Tree->remove(6,6);



    return 0;
}