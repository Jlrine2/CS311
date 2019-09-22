// ksarray.h
// James Rine
// Sep 11, 2019
// header and source for class KSArray

#ifndef KSARRAY_H_INCLDUED
#define KSARRAY_H_INCLDUED

#include <cstdlib>
#include <algorithm>


//ksarray class
//Invariants:
// _size is a positive 64bit integer type: _size > 0
// _arrPtr points to the first item of an array of value_type with >0 entries
//template pre:
// t is a type witch can be compared with < and ==
template<typename t>
class KSArray
{
public:
    //define size_type and value_type
    using size_type = std::size_t;
    using value_type = t;
private:
    //ptr to class KSArray
    value_type* _arrPtr;

    std::size_t _size;

    //swaps with other KSArray
    //pre:
    //other must be an R value, it will be changed
    //end: 
    //other will be trashed
    void mswap(KSArray & other){
        std::swap(_arrPtr, other._arrPtr); //only call on r values
        std::swap(_size, other._size);
    }
public:


    //default ctor
    KSArray(): 
    _size(8), 
    _arrPtr(new value_type[8]){
    }

    //ctor with size param
    //pre:
    //s param is a positive intager
    KSArray(int s): 
    _size(s), 
    _arrPtr(new value_type[s]){
    }

    //ctor with size and fill param
    //pre:
    //s param is a positive integer type
    KSArray(int s, value_type fill): 
    _size(s), 
    _arrPtr(new value_type[s]) {
        std::fill(_arrPtr, _arrPtr + _size, fill);
    }

    //Copy ctor
    KSArray(const KSArray & other): 
    _size(other.size()), 
    _arrPtr(new value_type[other.size()]) {
        std::copy(other.begin(), other.end(), _arrPtr);
    }

    //copy assignment
    KSArray & operator = (const KSArray & other) {
        KSArray copy(other); 
        mswap(copy); 
        return *this;
    }
    
    //move ctor
    //pre:
    //other must be an R value, it will be changed
    //end: other will be trashed
    //other will be trashed
    KSArray( KSArray && other) noexcept
    :_size(other.size()),
    _arrPtr(other._arrPtr){
        other._arrPtr = nullptr;
    }

    //move assignment
    //pre:
    //other must be an R value, it will be changed
    //end: other will be trashed
    //other will be trashed
    KSArray & operator = ( KSArray && other) noexcept{
        mswap(other);
        return *this;
    }

    //dctor
     ~KSArray(){
        delete [] _arrPtr;
    }


    //bracket operators
    //pre:
    //0 <= pos < size
    value_type & operator[](const std::size_t & pos){
        return _arrPtr[pos]; //*_arrPtr[pos];
    }

    //pre:
    //0 <= pos < size
    value_type & operator[](const std::size_t & pos) const {
        return _arrPtr[pos]; //*_arrPtr[pos];
    }

    //get size
    std::size_t size() const{
        return _size;
    }

    //iterator to beigning of const  array
    const value_type* begin() const{
        return _arrPtr;
    }

    //iterator to end of const array
    const value_type* end() const{
        return begin() + _size;
    }


    //iterator to beigning of array
    value_type* begin() {
        return _arrPtr;
    }

    //iterator to end of array
    value_type* end() {
        return begin() + _size;
    }
   
};
    
    //comarison operators
    //lexigraphical comparison this is < other
    //pre:
    // t must have a definition for operator <
    template<typename t>
    bool operator < (const KSArray<t> & lhs, const KSArray<t> & rhs){
        return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
    }  
   
    //canonical >= definition
    //pre:
    // t must have a definition for operator <
    template<typename t>
    bool operator >= (const KSArray<t> & lhs,const KSArray<t> & rhs) {
        return !(lhs < rhs); 
    }

    //canonical > definition
    //pre:
    // t must have a definition for operator <
    template<typename t>
    bool operator > (const KSArray<t> lhs, const KSArray<t> & rhs) {
        return rhs < lhs;
    }
 
    //canonical <= defininition
    //pre:
    // t must have a definition for operator <
    template<typename t>
    bool operator <= (const KSArray<t> & lhs, const KSArray<t> & rhs) {
        return !(lhs > rhs);
    }

    //define == based on std::equal algorithm
    //pre:
    // t must have a definition for operator ==
    template<typename t>
    bool operator ==(const KSArray<t> lhs, const KSArray<t> & rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    
    //canonical != definition
    //pre:
    // t must have a definition for operator ==
    template<typename t>
    bool operator !=(const KSArray<t> lhs, const KSArray<t> & rhs) {
        return !(lhs == rhs);
    }
 

#endif