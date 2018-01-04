#include <iostream>
#include "Colosseum.h"

using std::cout;
using std::endl;

int main() {

    int arr[5];
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 5;
    arr[3] = 4;
    arr[4] = 7;

    Colosseum colosseum(5, arr);
    colosseum.addTrainingGroup(11);
    colosseum.addTrainingGroup(20);
    colosseum.addTrainingGroup(14);
    colosseum.addTrainingGroup(1);

    return 0;
}