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
struct treeNode
{
    std::unique_ptr<treeNode<ValueType>> greaterChildTree;
    std::unique_ptr<treeNode<ValueType>> lessChildTree;
    ValueType data;
    
    
    treeNode(const ValueType & data):
    data(data)
    {}

    ~treeNode() = default;

    treeNode() = default;

    //delete copy and move operations
    treeNode(const treeNode & other) = delete;
    treeNode(const treeNode && other) = delete;
    treeNode & operator=(const treeNode & lhs) = delete;
    treeNode & operator=(const treeNode && lhs) = delete;

};


template<typename ValueType>
void insertTree(std::unique_ptr<treeNode<ValueType>> & tree,const ValueType & dataToInsert) {
    if (!tree) {
        tree = std::make_unique<treeNode<ValueType>>(dataToInsert);
        return;
    }
    if (tree ->data < dataToInsert) {
        insertTree(tree -> greaterChildTree, dataToInsert);
    }
    else {
        insertTree(tree -> lessChildTree, dataToInsert);
    }
}

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

    std::unique_ptr<treeNode<ValueType>> head;
    for (FDIter it = first; it != last; ++it) {
        insertTree(head, *it);
    }

    
    // THE FOLLOWING IS DUMMY CODE. IT WILL PASS ALL TESTS, BUT IT DOES
    // NOT MEET THE REQUIREMENTS OF THE PROJECT.
    std::vector<ValueType> buff(std::distance(first, last));
    std::move(first, last, buff.begin());
    std::stable_sort(buff.begin(), buff.end());
    std::move(buff.begin(), buff.end(), first);
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED

