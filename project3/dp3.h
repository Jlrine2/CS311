// dp3.h 
// James Rine
// 2019-09-30
//
// For CS 311 Fall 2019
// Header for Project 3 Functions

//This file is based of off dp3.h written by Glen Chappel:
//    https://projects.cs.uaf.edu/redmine/projects/cs311_2019_03/repository/changes/dp3.h


#ifndef FILE_DP3_H_INCLUDED
#define FILE_DP3_H_INCLUDED

#include <cstddef>     // For std::size_t
#include <algorithm>
#include <functional>  // For std::function


// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Invariants:                                                      // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValType must have a copy ctor and a (non-throwing) dctor.    // *
template <typename ValType>                                         // *
struct LLNode {                                                     // *
    ValType   _data;  // Data for this node                         // *
    LLNode *  _next;  // Ptr to next node, or nullptr if none       // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // _data is set to data (given). _next is set to next, if       // *
    // given, or nullptr if not.                                    // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it points // *
    //      to an LLNode allocated with new, with ownership         // *
    //      transferred to *this.                                   // *
    explicit LLNode(const ValType & data,                           // *
                    LLNode * next = nullptr)                        // *
        :_data(data),                                               // *
         _next(next)                                                // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Does delete on _next.                                        // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
                                                                    // *
    // No default ctor, copy, or move.                              // *
    LLNode() = delete;                                              // *
    LLNode(const LLNode & other) = delete;                          // *
    LLNode & operator=(const LLNode & other) = delete;              // *
    LLNode(LLNode && other) = delete;                               // *
    LLNode & operator=(LLNode && other) = delete;                   // *
                                                                    // *
};  // End struct LLNode                                            // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *



// lookup is given a pointer to a null-terminated Linked List and an integer index. 
// Similar to a bracket operator it retuns item coresponding to index.
// 
// Requirements on type:
// none
//
// lookup throws if index is >= size of linked list
template <typename ValueType>
ValueType lookup(const LLNode<ValueType> * head,
                 std::size_t index)
{
    //empty list check
    if (head==nullptr) 
        throw std::out_of_range("index out of range");
    

    for (std::size_t i = 0; i < index; ++i) {
        if (head -> _next == nullptr) {
            throw std::out_of_range("Index out of range");
        }
        head = head -> _next;
    }

    return head -> _data;  
    
}


// Implementation in source file
// didItThrow will trow the same exception as the function passed. 
// sets threw based on exceptions
void didItThrow(const std::function<void()> & ff,
                bool & threw);



// checkSorted will return true if list is sorted by < completely
// 
// Requirements on type:
// FDIter must be an iterator that can be forwardly incremented (with ++)
// FDIter must have == and != defined
// FDIter must point to a type comparable with <
//
// does not throw
template <typename FDIter>
bool checkSorted(FDIter first,
                 FDIter last)
{
    //*************************************************************************
    //     I've used a standard library function to solve this problem,      **
    //     but also included a version of my own writing commented below     **
    //     to demonstrate knowledge and understanding of the excersise.      **
    //*************************************************************************

    // //empty list check
    // if (first == last){
    //     return true;
    // }

    // FDIter current = first;
    // FDIter next = current;
    // ++next;

    
    // while (next != last){
    //     if (*next < *current){
    //         return false;
    //     }
    //     ++current;
    //     ++next;
    // }

    // return true; 

    return std::is_sorted(first, last);
}


// recursive function to find greatest common denominator between two numbers.
// PreConditions:
// a and b must be non negitive
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DP3_H_INCLUDED

