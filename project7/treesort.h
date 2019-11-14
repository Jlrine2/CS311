// treesort.h  SKELETON
// Glenn G. Chappell
// 2019-11-10
//
// For CS 311 Fall 2019
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <iterator>
// For std::iterator_traits
#include <algorithm>
// For std::stable_sort, std::move
#include <vector>
// For std::vector
#include <iterator>
// For std::distance
#include<memory>
// for std::unique_ptr, std::make_unique


template<typename ValueType>
class BinarySearchTree{
public:
    ///no default ctor must take data param
    BinarySearchTree() = delete;

    //default dctor
    ~BinarySearchTree() = default;

    //take a object to store in the root node
    BinarySearchTree(const ValueType & headData):
        data(headData),
        {}

    //delete copy and move ctor and assignment
    BinarySearchTree(const BinarySearchTree & other) = delete;
    BinarySearchTree & operator=(const BinarySearchTree & rhs) = delete;

    BinarySearchTree(const BinarySearchTree && other) = delete;
    BinarySearchTree & operator=(const BinarySearchTree && rhs) = delete;

public:
    
    void insert(const ValueType & dataToInsert){
        if (dataToInsert < data){
            insertToGreaterChild(dataToInsert);
        }
        else{
            insertToLessChild(dataToInsert);
        }
    }


private:

    void insertToGreaterChild(const ValueType & dataToInsert){
        if (greaterChildTree) {
            return greaterChildTree -> insert(dataToInsert);
        }
        greaterChildTree = std::make_unique<BinarySearchTree<ValueType>>(dataToInsert);
    }

    void insertToLessChild(const ValueType & dataToInsert) {
        if (greaterChildTree) {
            return greaterChildTree -> insert(dataToInsert);
        }
        greaterChildTree = std::make_unique<BinarySearchTree<ValueType>>(dataToInsert);
    }

    //private data members
    std::unique_ptr<BinarySearchTree<ValueType>> lessChildTree;
    std::unique_ptr<BinarySearchTree<ValueType>> greaterChildTree;
    ValueType data;
};


// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Requirements on Types:
//     must be copyable
//     
// Exception safety guarantee:
//     ???
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // ValType is the type that FDIter points to
    using ValueType = typename std::iterator_traits<FDIter>::value_type;

    BinarySearchTree<ValueType> BSTree(*first);
    auto it = first;
    ++it;
    for (it; it != last; ++it) {
        BSTree.insert(*it);
    }
    
    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS, BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE PROJECT.
    std::vector<ValueType> buff(std::distance(first, last));
    std::move(first, last, buff.begin());
    std::stable_sort(buff.begin(), buff.end());
    std::move(buff.begin(), buff.end(), first);
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED

