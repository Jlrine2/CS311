//inventoryitem.cpp
//James Rine
//Sep 7, 2019
//Source file for Inventory Item Class

#include "inventoryitem.h"
#include <string>

//get functions for InventoryItem name and number
std::string InventoryItem::getName() const{
    return _name;
}
int InventoryItem::getNumber() const{
    return _number;
}

//set functions for InventoryItem name and number
void InventoryItem::setName(std::string n){
    _name = n;
}
void InventoryItem::setNumber(int x){
    _number = x;
}

//check if item is in or out of stock
bool InventoryItem::empty() const{
    return !_number;
}

//return a string with the format "name (number)"
std::string InventoryItem::toString() const{
   return _name + " (" + std::to_string(_number) + ")";
}

//increment operators
InventoryItem & InventoryItem::operator++(){
    ++_number;
    return *this;
}
InventoryItem InventoryItem::operator++(int dummy){
    auto save = *this;
    ++*this;
    return save;
}

//decrement operators
InventoryItem & InventoryItem::operator--(){
    if (_number > 0) {
        --_number;
    }
    return *this;
}
InventoryItem InventoryItem::operator-- (int dummy){
    auto save = *this;
    --*this;
    return save;
}

//equivelency
bool operator == (const InventoryItem & lhs, const InventoryItem & rhs){
    return (lhs.getNumber() == rhs.getNumber()) && (lhs.getName() == rhs.getName());
}
bool operator != (const InventoryItem & lhs, const InventoryItem & rhs){
    return !(lhs==rhs);
}

//stream inserion
std::ostream & operator<<(std::ostream & out, const InventoryItem & inv){
    out << inv.toString();
    return out;
}