#include <iostream>
#include "board.h"
#include "tetris.h"


using namespace std;



int main() {
    board a(5);
    a.displayGrid();

    tetris test(10);
    test.loadJson("Tetris03");





    return 0;
}
