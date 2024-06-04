#ifndef MOTION2D
#define MOTION2D
#include <iostream>

// Predefined constant for pi, to be used if/when converting degrees
// to radians.
#define PI 3.14159265

// Forward declation of Force. Needed in case any of Point references
// the existence of type Force.
class Force;

class Point {
    // Private fields and helpers here.
    float x{}, y{};
  public:
    // Required public interface here.
    friend std::istream& operator>>(std::istream& is, Point& point);
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
    Point operator+(const Force& force) const;
    int quadrant() const;
};

class Force {
    // Private fields and helpers here.
    float angle{}, magnitude{};
  public:
    // Required public interface here.
    friend std::istream& operator>>(std::istream& is, Force& force);
    friend std::ostream& operator<<(std::ostream& os, const Force& force);
    friend Point Point::operator+(const Force& force) const;
    Force operator*(int m) const;
};

#endif
