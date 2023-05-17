#include "Character.hpp"
#include <stdlib.h>

ariel::Character::Character(const std::string& name, const ariel::Point& position, int healthPoints):
    name{name}, position{position}, healthPoints{healthPoints} { 
}
bool ariel::Character::isAlive() const{
    return false;
}
double ariel::Character::distance(const Character* other) const{
    return -1;
}
void ariel::Character::hit(int damage){
    return;
}
std::string ariel::Character::getName() const{
    return "";
}
ariel::Point ariel::Character::getLocation() const{
    return ariel::Point(0,0);
}
ariel::Ninja::Ninja(const std::string& name, const ariel::Point& position, int healthPoints, int velocity) : Character(name, position, healthPoints){
    return;
}
void ariel::Ninja::move(const Character * other){
    return;
}
void ariel::Ninja::slash(Character * other){
    return;
}
std::string ariel::Ninja::print() const{
    return "";
}
ariel::YoungNinja::YoungNinja(const std::string& name, const ariel::Point& position) : Ninja(std::string(), ariel::Point(0,0), 0, 0){
}
ariel::TrainedNinja::TrainedNinja(const std::string& name, const ariel::Point& position) : Ninja(std::string(), ariel::Point(0,0), 0, 0){
}
ariel::OldNinja::OldNinja(const std::string& name, const ariel::Point& position) : Ninja(std::string(), ariel::Point(0,0), 0, 0){
}
ariel::Cowboy::Cowboy(const std::string& name, const ariel::Point& position) : Character(std::string(), ariel::Point(0,0), 0){
}
void ariel::Cowboy::shoot(Character * other){
    return;
}
void ariel::Cowboy::reload(){
    return;
}
bool ariel::Cowboy::hasboolets() const{
    return false;
}
std::string ariel::Cowboy::print() const{
    return "";
}
int ariel::Character::getHealthPoints() const{
    return 0;
}
std::string ariel::Character::getcharacterName() const{
    return std::string();
}