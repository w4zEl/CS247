#ifndef REGEXP_H
#define REGEXP_H
#include <string>
#include <utility>
#include <iostream>

class RegExp { // No implementation necessary
 public:
  virtual bool matches(const std::string &s) = 0;
  virtual std::ostream &print(std::ostream &out) = 0;

  virtual ~RegExp() {};
};

class Char: public RegExp {
  char c;
 public:
  Char(char c); // Implement
  bool matches(const std::string &s) override; // Implement

  std::ostream &print(std::ostream &out) override; // Provided
};

class Disjunction: public RegExp {
  RegExp* left, *right;
 public:
  Disjunction(RegExp* left, RegExp* right); // Implement
  ~Disjunction(); // Implement
  bool matches(const std::string &s) override; // Implement

  std::ostream &print(std::ostream &out) override; // Provided
};

class Concatenation: public RegExp {
  RegExp* left, *right;
 public:
  Concatenation(RegExp* left, RegExp* right); // Implement
  ~Concatenation(); // Implement
  bool matches(const std::string &s) override; // Implement

  std::ostream &print(std::ostream &out) override; // Provided
};

class Star: public RegExp {
  RegExp* arg;
 public:
  Star(RegExp* arg); // Implement
  ~Star(); // Implement
  bool matches(const std::string &s) override; // Implement

  std::ostream &print(std::ostream &out) override; // Provided
};

std::ostream &operator<<(std::ostream &out, RegExp &re); // Provided

RegExp* parseDisjunction(const std::string &s); // Provided
RegExp* parseConcatenation(const std::string &s); // Provided
RegExp* parseStar(const std::string &s); // Provided
RegExp* parseChar(const std::string &s); // Provided

#endif
