//inventoryitem.h
//James Rine
//Sept 6 2019
//header file for InventoryItem class


#ifndef INVENTORY_ITEM_INCLUDED
#define INVENTORY_ITEM_INCLUDED


#include <string>
#include <ostream>

//Class InventoryItem holds name of item and number
//
//invariants:
//number >=0 (will be set to zero if less then)
class InventoryItem {
private:
    std::string _name;
    int _number; // number >=0
public:
    //ctors
    InventoryItem(): _name("UNNAMED"), _number(0){
    }
    InventoryItem(std::string n, int x): _name(n), _number(x){
        if (_number < 0) //dissallow negitive numbers
        {
            _number = 0;
        }
    }
    //default big 5
    ~InventoryItem() = default; 
    InventoryItem(const InventoryItem & a) = default;
    InventoryItem(InventoryItem && a) = default;
    InventoryItem & operator = (const InventoryItem & a) = default;
    InventoryItem & operator = (InventoryItem && a) = default;


    //get functions return values in name and number respectivly
    std::string getName() const;
    int getNumber() const;

    //set functions to change values in name of number
    void setName(std::string n);
    void setNumber(int x);

    //checks if item is in stock, returns false if number is greater then 0
    bool empty() const;

    //returns a string format of the inventory item "name (number)"
    std::string toString() const;

    //increment number
    InventoryItem & operator ++ ();
    InventoryItem operator ++ (int dummy);

    //decrement number
    InventoryItem & operator -- ();
    InventoryItem operator -- (int dummy);

};

//equivelency operator
bool operator == (const InventoryItem & lhs, const InventoryItem & rhs);
bool operator != (const InventoryItem & lsh, const InventoryItem & rhs);

//stream inserion operator
std::ostream & operator << (std::ostream & out, const InventoryItem & inv);


#endif