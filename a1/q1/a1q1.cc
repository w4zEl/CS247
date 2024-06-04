#include <iostream>
#include <iomanip>
#include "2DMotion.h"
using namespace std;

void invalidTarget(char target) {
    cout << "Invalid test case! ";
    cout << "Invalid target for new command: '";
    cout << target << "'" << endl;
}

int main() {
    Point p;
    Force f;
    cout << fixed << setprecision(2);
    char cmd, target;
    int scalar;
    while (cin >> cmd) {
        switch (cmd) {
            // Command for creating a new point or force. Expects
            // either p or f next for point or force respectively.
            // Then reads in the object.
            case 'n':
                cin >> target;
                if (target == 'p') {
                    cin >> p;
                } else if (target == 'f') {
                    cin >> f;
                } else {
                    invalidTarget(target);
                }
                break;
            // Command for printing the point or force. Expects either
            // p or f next for point or force respectively. Then prints
            // out the appropriate object.
            case 'p':
                cin >> target;
                if (target == 'p') {
                    cout << p << endl;
                } else if (target == 'f') {
                    cout << f << endl;
                } else {
                    invalidTarget(target);
                }
                break;
            // Updates the current point to be the addition of the
            // current point with the force.
            case '+':
                p = p + f;
                break;
            // Updates the current force by multiplying it by a scalar
            // read in. Reads in an int after *.
            case '*':
                cin >> scalar;
                f = f * scalar;
                break;
            // Prints out the current points quadrant.
            case 'q':
                cout << p.quadrant() << endl;
                break;
            default:
                cout << "Invalid test case! ";
                cout << "Invalid command: '" << cmd << "'" << endl; 
                break;
            
        }
    }
    if (!cin && !cin.eof()) {
        cout << "Invalid test case! ";
        cout << "A read failed, likely because the program was trying";
        cout << " to read a number and didn't receive it. ";
        cout << "Make sure your test case is valid!" << endl;
        return -1;
    }
    return 0;
}
