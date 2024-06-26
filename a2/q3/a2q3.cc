#include <iostream>
#include <string>
#include "regexp.h"
using namespace std;

int main() {
  string s;
  while (getline(cin, s)) {
    RegExp* re = parseDisjunction(s);
    cout << "RegExp is: " << *re << endl;
    while (getline(cin, s)) {
      if (s == "q") break;
      cout << boolalpha << re->matches(s) << endl;
    }
    delete re;
  }
}
