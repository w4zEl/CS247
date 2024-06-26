#include <iostream>
#include "list.h"
using namespace std;

// operator << to test iteration
template<typename T> std::ostream &operator<<(std::ostream &out, const List<T> &l) {
  out << l.size() << std::endl;
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    out << *it << std::endl;
  }
  return out;
}

// Sets all nodes in the list to 0 (for ints), or the empty string (for strings)

template <typename T> void zeroAllNodes(List<T>& l) {
    for (auto& v : l) {
        v = T{};
    }
}

template <typename T> void processInput(List<T>** array) {
    char command;
    int list1, list2;
    cin >> command;
    cin >> list1;

    switch (command) {
        // New list
        case 'n':
            array[list1] = new List<T>{};
            break;
        // Print list
        case 'p':
            cout << *array[list1];
            break;
        // pUsh onto list
        case 'u': {
            T toPush;
            cin >> toPush;
            array[list1]->push(toPush);
            break;
        }
        // pOp from list
        case 'o':
            array[list1]->pop();
            break;

        // zero-out list (zero for int lists, empty string for string list)
        case 'z':
            zeroAllNodes(*array[list1]);
            break;

        // delete list
        case 'd':
            delete array[list1];
            array[list1] = nullptr;
            break;

        // Copy construct
        case 'c':
            cin >> list2;
            delete array[list1];
            array[list1] = new List<T>{*array[list2]};
            break;

        // Move construct
        case 'm':
            cin >> list2;
            delete array[list1];
            array[list1] = new List<T>{std::move(*array[list2])};
            delete array[list2];
            array[list2] = nullptr;
            break;

        // Copy assignment operator
        case 'C':
            cin >> list2;
            *array[list1] = *array[list2];
            break;

        // Move assignment operator
        case 'M':
            cin >> list2;
            *array[list1] = std::move(*array[list2]);
            delete array[list2];
            array[list2] = nullptr;
            break;

        default:
            cerr << "Invalid command" << endl;

    }
}

int main () {
    List<string>* stringLists[4] = {nullptr};
    List<int>* intLists[4] = {nullptr};

    while (true) {
        char listType;
        cin >> listType;
        if (!cin) break;
        if (listType == 's') {
            processInput(stringLists);
        } else if (listType == 'i') {
            processInput(intLists);
        } else {
            cerr << "Invalid list type" << endl;
        }
    }
    
    for ( int i = 0 ; i < 4; ++i ) {
        delete stringLists[i];
        delete intLists[i];
    }
} // main
