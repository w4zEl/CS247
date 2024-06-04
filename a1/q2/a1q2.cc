#include <iostream>
#include <iostream>
#include <utility>
#include "Battleship.h"
using namespace std;

int main() {
    const size_t NUM_BOARDS = 4;
    // Our boards, we refer to them as a, b, c, and d respectively.
    Battleship *boards[NUM_BOARDS] = {nullptr, nullptr, nullptr, nullptr};
    char cmd, lhs, rhs;
    int nr, nc;
    // A board cannot be used for operations until it is constructed.
    // NOTE: If a board (a, b, c, d) is moved from then it is not longer
    // a valid object to be used for any operations (until you create 
    // a new board in that location). Moved from boards are nulled out
    // after being moved from to help you realize this.
    while (cin >> cmd && cmd != 'q') {
        switch (cmd) {
            // Command to create a new board. After 'n' we read which board to create,
            // and then 2 naturals, first number of rows, then number of columns
            case 'n':
                cin >> lhs >> nr >> nc;
                delete boards[lhs-'a'];
                boards[lhs-'a'] = new Battleship{nr, nc};
                break;
            // Command to invoke copy constructor to create a new board.
            // After 'c' expects to read which board to create, and 
            // then which board to copy.
            case 'c':
                cin >> lhs >> rhs;
                delete boards[lhs-'a'];
                boards[lhs-'a'] = new Battleship{*boards[rhs-'a']};
                break;
            // Command to invoke move constructor to create a new board.
            // After 'm' expects to read which board to create, and
            // then which board to move from.
            case 'm':
                cin >> lhs >> rhs;
                delete boards[lhs-'a'];
                boards[lhs-'a'] = new Battleship{move(*boards[rhs-'a'])};
                delete boards[rhs-'a'];
                boards[rhs-'a'] = nullptr;
                break;
            // Command to invoke copy assignment operator to copy
            // assign one board to another. After reading 'a' expects
            // to see which board to be assigned, and then which board
            // to copy from.
            case 'a':
                cin >> lhs >> rhs;
                *boards[lhs-'a'] = *boards[rhs-'a'];
                break;
            // Command to invoke move assignment operator to move
            // assign one board to another. After reading 'v' expets
            // to see which board to be assigned, and then which board
            // to move from. 
            case 'v':
                cin >> lhs >> rhs;
                *boards[lhs-'a'] = move(*boards[rhs-'a']);
                delete boards[rhs-'a'];
                boards[rhs-'a'] = nullptr;
                break;
            // Command to play one turn on the target board. Expects
            // to receive which board to play on after reading 't'.
            case 't':
                cin >> lhs;
                boards[lhs-'a']->playTurn();
                break;
            // Command to print target board. Expects to receive which
            // board to print after reading 'p'.
            case 'p':
                cin >> lhs;
                cout << "Printing board " << lhs << endl;
                cout << *boards[lhs-'a'];
                break;
            // Command to read into a target board
            // Continually reads 2 pairs of naturals: (r1, c1, r2, c2) which define a starting location
            // and ending location where a ship is placed.
            // Must check that ships are placed horizontally or vertically.
            // Stops reading after 5 successful ships placed, or a non-numeric character is entered on stdin.
            case 'r':
                cin >> lhs;
                cout << "Reading into board " << lhs << endl;
                cin >> *boards[lhs-'a'];
                break;
            default:
                cout << "Invalid test case! ";
                cout << "Invalid command: '" << cmd << "'" << endl;
        }   
    }
    for (size_t i = 0; i < NUM_BOARDS; ++i) delete boards[i];
    if (!cin && !cin.eof()) {
        cout << "Invalid test case! ";
        cout << "A read failed, likely because the program was trying";
        cout << " to read a number and didn't receive it. ";
        cout << "Make sure your test case is valid!" << endl;
        return -1;
    }
    return 0;
}
