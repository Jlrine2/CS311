// tssarray.h
// based on version 5 of ssarray.h:
// Glenn G. Chappell
// Started: 2019-10-16
// Updated: 2019-10-23
//
// For CS 311 Fall 2019
// Header for class SSArray
// Seriously smart array template

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <cstdlib>
// For std::size_t
#include <algorithm>
// For std::max


// *********************************************************************
// class SSArray - Class definition
// *********************************************************************


// class SSArray
// Seriously Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of int, allocated with new[], owned by
//      *this, holding _size ints -- UNLESS _capacity == 0, which case
//      _data may be nullptr.
template<user_defined_type>
class SSArray {

// ***** SSArray: types *****
public:

    // value_type: type of data items
    using value_type = user_defined_type;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** SSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 8 };

// ***** SSArray: ctors, op=, dctor
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    explicit SSArray(size_type size=0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    SSArray(const SSArray & other);

    // Move ctor
    // No-Throw Guarantee
    SSArray(SSArray && other) noexcept;

    // Dctor
    // No-Throw Guarantee
    ~SSArray()
    {
        delete [] _data;
    }

    // Copy assignment
    // ??? Guarantee
    SSArray & operator=(const SSArray & rhs);

    // Move assignment
    // No-Throw Guarantee
    SSArray & operator=(SSArray && rhs) noexcept;

// ***** SSArray: general public operators *****
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

// ***** SSArray: general public functions *****
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

    // resize
    // ??? Guarantee
    void resize(size_type newsize);

    // insert
    // ??? Guarantee
    iterator insert(iterator pos,
                    const value_type & item);

    // erase
    // ??? Guarantee
    iterator erase(iterator pos);

    // push_back
    // ??? Guarantee
    void push_back(value_type item)
    {
        insert(end(), item);
    }

    // pop_back
    // ??? Guarantee
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    void swap(SSArray & other) noexcept;

// ***** SSArray: data members *****
private:

    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class SSArray


#endif //#ifndef FILE_SSARRAY_H_INCLUDED

