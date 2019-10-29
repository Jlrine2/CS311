// tssarray.h
// based on version 5 of ssarray.h:
// Glenn G. Chappell
// Started: 2019-10-16
// Updated: 2019-10-23
//
// For CS 311 Fall 2019
// Header for class TSSArray
// Seriously smart array template

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <cstdlib>
// For std::size_t
#include <algorithm>
// For std::max, std::copy

// *********************************************************************
// class TSSArray - Class definition
// *********************************************************************


// class TSSArray
// Seriously Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of int, allocated with new[], owned by
//      *this, holding _size ints -- UNLESS _capacity == 0, which case
//      _data may be nullptr.
template<typename user_defined_type>
class TSSArray {

// ***** TSSArray: types *****
public:
    // value_type: type of data items
    using value_type = user_defined_type;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** TSSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 8 };

// ***** TSSArray: ctors, op=, dctor
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    explicit TSSArray(size_type size=0)
        //capacity set to double size for resizing efficiancy
        :_capacity(std::max(size*2, size_type(DEFAULT_CAP))),
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    TSSArray(const TSSArray & other)
        :_capacity(other._capacity),
         _size(other._size),
         _data(new value_type[_capacity]) {
             try{
                 std::copy(other.begin(), other.end(), begin()); // may throw
             }
            catch(...) {
                delete [] _data;
                _capacity = 0;
                _size = 0;
                _data = nullptr;
                throw;
            }
        }

    // Move ctor
    // No-Throw Guarantee
    TSSArray(TSSArray && other) noexcept
        :_capacity(other._capacity),
         _size(other._size),
         _data(other._data) {
             other._capacity = 0;
             other._size = 0;
             other._data = nullptr;
         }

    // Dctor
    // No-Throw Guarantee
    ~TSSArray()
    {
        delete [] _data;
    }

    // Copy assignment
    // Strong Guarantee
    TSSArray & operator=(const TSSArray & rhs){
        try{
            TSSArray copy(rhs); // may throw
            //copy is R value and can be totally ruined
            swap(copy); //will not throw
        }
        catch(...){
            delete [] _data;
            _capacity = 0;
            _size = 0;
            _data = nullptr;
            throw;
        }
        return *this;
    }

    // Move assignment
    // No-Throw Guarantee
    TSSArray & operator=(TSSArray && rhs) noexcept{
        swap(rhs);
        return *this;
    }

// ***** TSSArray: general public operators *****
public:

    // Operator[] - non-const & const
    // No-Throw Guarantee
    value_type & operator[](size_type index) noexcept
    {
        return _data[index];
    }
    const value_type & operator[](size_type index) const noexcept
    {
        return _data[index];
    }

// ***** TSSArray: general public functions *****
public:

    // size
    // No-Throw Guarantee
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    iterator begin() noexcept
    {
        return _data;
    }
    const_iterator begin() const noexcept
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    iterator end() noexcept
    {
        return begin() + size();
    }
    const_iterator end() const noexcept
    {
        return begin() + size();
    }

public: //REMOVE ME!!!!!!!!!!!!!!!!!!!!!!!!!!!


    // resize
    // Strong Guarantee
    // No-Throw if newsize <= _capacity
    void resize(size_type newsize) {
        if (newsize <= _capacity) {
            _size = newsize;
            return;
        }
        //create copy with capacity twice size needed
        TSSArray copy(newsize);
        //move values to copy may throw
        try { std::copy(begin(), end(), copy.begin()); }
        catch(...) {
            delete [] _data;
            _capacity = 0;
            _size = 0;
            _data = nullptr;
            throw;
        }

        swap(copy);
    }

    // insert
    // Basic Guarantee
    iterator insert(iterator pos,
                    const value_type & item){
        //incase we reallocate and copy
        size_type index = pos - _data;

        push_back(item);

        iterator newpos = index + _data;

        std::rotate(newpos, end() - 1, end());

        return newpos;
    }

    // erase
    // Basic Guarantee
    iterator erase(iterator pos){
        std::rotate(pos, pos + 1, end());
        pop_back();
        return pos;
    }

    // push_back
    // Basic Guarantee
    void push_back(const value_type & item)
    {
        resize(size() + 1);
        try {
        *(end()-1) = item;
        }
        catch(...) {
            this -> ~TSSArray();
            throw;
        }
    }

    // pop_back
    // No-Throw Guarantee
    void pop_back()
    {
        resize(size() - 1);
    }

    // swap
    // No-Throw Guarantee
    void swap(TSSArray & other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);

    }



// ***** TSSArray: data members *****
private:
    //capacity must be declared before _size in order to use it in member initialization
    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class TSSArray


#endif //#ifndef FILE_SSARRAY_H_INCLUDED

