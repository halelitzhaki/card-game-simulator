#include "card.hpp"

using namespace ariel;

Card::Card(){}

Card::Card(int _number, string _name){
    number = _number;
    name = _name;
}

Card::~Card() { }

int Card::getNumber() {
    return number;
}

string Card::getName() {
    return name;
}
