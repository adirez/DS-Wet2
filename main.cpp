#include <iostream>
#include "Colosseum.h"

using std::cout;
using std::endl;

int main() {

    int arr[2];
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 5;
    arr[3] = 4;
    arr[4] = 7;

    Colosseum colosseum(2, arr);
    colosseum.addGladiator(20, 10, 3);

    return 0;
}