#include "Battleship.h"
#include <utility>
#include <iostream>
Battleship::Battleship(int r, int c) : nr{r}, nc{c}, board{new char*[r]} {
    for (int y = 0; y < r; ++y) board[y] = new char[c]();
}
Battleship::Battleship(const Battleship& other) : Battleship{other.nr, other.nc} {
    for (int y = 0; y < nr; y++)
        for (int x = 0; x < nc; x++)
            board[y][x] = other.board[y][x];
    for (int i = shipCount = other.shipCount; i--;) shipArray[i] = other.shipArray[i];
}
Battleship::Battleship(Battleship&& other) : nr{other.nr}, nc{other.nc}, board{other.board}, shipCount{other.shipCount} {
    other.board = nullptr;
    other.nr = 0;
    std::swap(shipArray, other.shipArray);
}
Battleship& Battleship::operator=(const Battleship& other) {
    return *this = Battleship{other};
}
Battleship& Battleship::operator=(Battleship&& other) {
    std::swap(board, other.board);
    std::swap(nr, other.nr);
    nc = other.nc;
    shipCount = other.shipCount;
    std::swap(shipArray, other.shipArray);
    return *this;
}
Battleship::~Battleship() {
    while (nr--) delete[] board[nr];
    delete[] board;
}
std::ostream& operator<<(std::ostream& os, const Battleship& battleship) {
    for (int y = 0; y < battleship.nr; ++y) {
        for (int x = 0; x < battleship.nc; ++x) os << battleship.SEP << (battleship.board[y][x] ? battleship.board[y][x] : battleship.OPEN_SPACE);
        os << battleship.SEP << '\n';
    }
    return os;
}
bool Battleship::intersects(const ShipLocation& check) {
    for (int i = 0; i < shipCount; ++i) {
        auto& shipLoc = shipArray[i];
        if (check.r1 <= shipLoc.r2 && check.r2 >= shipLoc.r1 && check.c1 <= shipLoc.c2 && check.c2 >= shipLoc.c1) return true;
    }
    return false;
}
std::istream& operator>>(std::istream& is, Battleship& battleship) {
    for (int y = 0; y < battleship.nr; ++y)
        for (int x = 0; x < battleship.nc; ++x)
            battleship.board[y][x] = 0;
    for (battleship.shipCount = 0; battleship.shipCount < battleship.MAX_SHIPS;) {
        auto& shipLoc = battleship.shipArray[battleship.shipCount];
        if (!(is >> shipLoc.r1 >> shipLoc.c1 >> shipLoc.r2 >> shipLoc.c2)) {
            is.clear();
            is.get();
            break;
        }
        if (shipLoc.r1 > shipLoc.r2 || shipLoc.c1 > shipLoc.c2) {
            std::swap(shipLoc.r1, shipLoc.r2);
            std::swap(shipLoc.c1, shipLoc.c2);
        }
        if (shipLoc.r1 >= 0 && shipLoc.r1 < battleship.nr && shipLoc.r2 >= 0 && shipLoc.r2 < battleship.nr
            && shipLoc.c1 >= 0 && shipLoc.c1 < battleship.nc && shipLoc.c2 >= 0 && shipLoc.c2 < battleship.nc
            && ((shipLoc.r1 == shipLoc.r2) ^ (shipLoc.c1 == shipLoc.c2)) && !battleship.intersects(shipLoc))
            ++battleship.shipCount;
        else std::cout << "Invalid coordinates\n";
    }
    return is;
}
void Battleship::playTurn() {
    std::cout << "Enter a row and column\n";
    for (int r, c; std::cin >> r >> c;) {
        if (r >= 0 && r < nr && c >= 0 && c < nc && !board[r][c]) {
            if (intersects({r, c, r, c})) {
                std::cout << "Hit!\n";
                board[r][c] = HIT;
            } else {
                std::cout << "Miss!\n";
                board[r][c] = MISS;
                return;
            }
        } else std::cout << "Invalid move! Try again\n";
    }
    std::cin.clear();
    std::cin.get();
}
