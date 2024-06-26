#include "regexp.h"
#include <string>
Char::Char(char c) : c{c} {}
bool Char::matches(const std::string& s) {
    return s.size() == 1 && s[0] == c; // char only matches single character string exactly
}
Disjunction::Disjunction(RegExp* left, RegExp* right) : left{left}, right{right} {}
Disjunction::~Disjunction() {
    delete left;
    delete right;
}
bool Disjunction::matches(const std::string& s) {
    return left->matches(s) || right->matches(s);
}
Concatenation::Concatenation(RegExp* left, RegExp* right) : left{left}, right{right} {}
Concatenation::~Concatenation() {
    delete left;
    delete right;
}
bool Concatenation::matches(const std::string& s) {
    for (decltype(s.size()) i = 0; i <= s.size(); ++i)
        if (left->matches(s.substr(0, i)) && right->matches(s.substr(i))) // try all splits
            return true;
    return false;
}
Star::Star(RegExp* arg) : arg{arg} {}
Star::~Star() {
    delete arg;
}
bool Star::matches(const std::string& s) {
    if (s.empty()) return true; // * can match nothing
    for (decltype(s.size()) i = 1; i <= s.size(); ++i)
        if (arg->matches(s.substr(0, i)) && matches(s.substr(i)))
            return true;
    return false;
}
