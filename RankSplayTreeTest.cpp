//
// Created by Shahak on 03/01/2018.
//

#include "RankSplayTree.h"
#include <iostream>

int main() {

    RankSplayTree<int, int> *Tree = new RankSplayTree<int, int>();
    Tree->insert(111,1);
    Tree->insert(333,2);
    Tree->insert(22,7);
    Tree->insert(77,20);
    Tree->insert(98,5);
    Tree->insert(71,13);
    Tree->insert(69,9);
    Tree->insert(1000,0);
    Tree->insert(62,6);
    Tree->insert(301,30);
    int best10 = Tree->getBestK(10);
    int best9 = Tree->getBestK(9);
    int best8 = Tree->getBestK(8);
    int best7 = Tree->getBestK(7);
    int best6 = Tree->getBestK(6);
    int best5 = Tree->getBestK(5);
    int best4 = Tree->getBestK(4);
    int best3 = Tree->getBestK(3);
    int best2 = Tree->getBestK(2);
    int best1 = Tree->getBestK(1);
    int best0 = Tree->getBestK(0);

    return 0;
}