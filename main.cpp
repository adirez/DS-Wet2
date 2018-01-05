#include <iostream>
#include "Colosseum.h"

using std::cout;
using std::endl;

int main() {

    int arr[3];
    arr[0] = 2;
    arr[1] = 7;
    arr[2] = 4;


    Colosseum colosseum(3, arr);
    colosseum.addTrainingGroup(3);
    colosseum.addTrainingGroup(1);
    colosseum.addGladiator(11, 40, 3);
    colosseum.addGladiator(22, 30, 3);
    colosseum.addGladiator(33, 12, 3);
    colosseum.addGladiator(44, 1, 3);
    colosseum.addTrainingGroup(6);

    return 0;
}