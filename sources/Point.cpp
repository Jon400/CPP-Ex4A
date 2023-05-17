#include "Point.hpp"

ariel::Point::Point(double x, double y){
    this->x = x;
    this->y = y;
}
ariel::Point::Point(const ariel::Point& other){
    this->x = other.x;
    this->y = other.y;
}
ariel::Point& ariel::Point::operator=(const Point& other){
    return *this;
}
ariel::Point::~Point(){
}
double ariel::Point::distance(const Point& other) const{
    return -1;
}
double ariel::Point::getX() const{
    return -1;
}
double ariel::Point::getY() const{
    return -1;
}
void ariel::Point::print() const{
}
ariel::Point ariel::moveTowards(const ariel::Point& source, const ariel::Point& destination, double distance){
    return ariel::Point(0,0);
}