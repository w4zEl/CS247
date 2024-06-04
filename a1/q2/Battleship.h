#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <iostream>

struct ShipLocation {
    int r1, c1, r2, c2;
};

class Battleship {
    const char OPEN_SPACE = ' ';
    const char MISS = 'o';
    const char HIT = 'X';
    const char SEP = '|';
    const int MAX_SHIPS = 5;

    int nr, nc;
    char **board;
    ShipLocation shipArray[5];
    int shipCount = 0;

    bool intersects(const ShipLocation&);
  public:
    Battleship(int, int);
    Battleship(const Battleship &);
    Battleship(Battleship &&);
    Battleship& operator=(const Battleship&);
    Battleship& operator=(Battleship&&);
    ~Battleship();
    
    void playTurn();
    
    friend std::ostream& operator<<(std::ostream &, const Battleship &);
    friend std::istream& operator>>(std::istream &, Battleship&);
};
#endif
