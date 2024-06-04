#include "2DMotion.h"
#include <iostream>
#include <cmath>
std::istream& operator>>(std::istream& is, Point& point) {
    return is >> point.x >> point.y;
}
std::istream& operator>>(std::istream& is, Force& force) {
    return is >> force.angle >> force.magnitude;
}
std::ostream& operator<<(std::ostream& os, const Point& point) {
    return os << '(' << point.x << ", " << point.y << ')';
}
std::ostream& operator<<(std::ostream& os, const Force& force) {
    return os << force.angle << " degrees with magnitude of " << force.magnitude;
}
Point Point::operator+(const Force& force) const {
    auto angleRad = force.angle * PI / 180;
    Point res;
    res.x = x + force.magnitude * std::cos(angleRad);
    res.y = y + force.magnitude * std::sin(angleRad);
    return res;
}
Force Force::operator*(int m) const {
    Force res{*this};
    res.magnitude *= m;
    return res;
}
int Point::quadrant() const {
    if (x < 0) return y < 0 ? 3 : 2;
    return y < 0 ? 4 : 1;
}
