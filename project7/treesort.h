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


// treeNode
// node for binary seach tree
// Requirements on Types:
//     ValueType must be copyable
// Exception safety guarantee:
//     strong
template<typename ValueType>
struct treeNode
{
    std::unique_ptr<treeNode<ValueType>> greaterChildTree;
    std::unique_ptr<treeNode<ValueType>> lessChildTree;
    ValueType data;
    
    treeNode(const ValueType & data):
    data(data) //may throw, let propigate out
    {}

    ~treeNode() = default;

    treeNode() = default;

    //delete copy and move operations
    treeNode(const treeNode & other) = delete;
    treeNode(const treeNode && other) = delete;
    treeNode & operator=(const treeNode & lhs) = delete;
    treeNode & operator=(const treeNode && lhs) = delete;

};

// insertTree
// inserts given data item into tree, equal items are stored as lessthan to maintain stability when read back out
// Requirements on Types:
//     ValueType must be copyable
// Exception safety guarantee:
//     strong
template<typename ValueType>
void insertTree(std::unique_ptr<treeNode<ValueType>> & tree,const ValueType & dataToInsert) {
    if (!tree) {
        tree = std::make_unique<treeNode<ValueType>>(dataToInsert); //may throw when calling ctor, let propigate out
        return;
    }
    if (dataToInsert < tree -> data) {
        insertTree(tree -> lessChildTree, dataToInsert);
    }
    else {
        insertTree(tree -> greaterChildTree, dataToInsert);
    }
}


// traverseTree
// passed a function, calls it on every item in tree in order (lessthan order)
// Pre:
//     function must take 1 parameter, a location to copy to, 
//     function must handle updating location between calls
// Requirements on Types:
//     ValueType must be copyable
//     
// Exception safety guarantee:
//     strong
template<typename ValueType, typename func>
void traverseTree(std::unique_ptr<treeNode<ValueType>> & head, func & function) {
    if (head -> lessChildTree) {
        traverseTree(head -> lessChildTree, function);
    }
    function(head -> data);

    if (head -> greaterChildTree) {
        traverseTree(head -> greaterChildTree, function);
    }
}


// treesort
// Sort a given range using Treesort.

// Requirements on Types:
//     ValueType must be copyable
//     
// Exception safety guarantee:
//     strong
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // ValType is the type that FDIter points to
    using ValueType = typename std::iterator_traits<FDIter>::value_type;

    //don't sort an empty container
    if (first == last){
        return;
    }

    std::unique_ptr<treeNode<ValueType>> head;

    //iterate through container and add each item to tree
    for (FDIter it = first; it != last; ++it) {
        insertTree(head, *it);
    }

    //copy out is a lamda function that is passed to traverse tree to copy data back into container,
    FDIter it = first;
    auto copyOut = [&] (ValueType & data) {
            *it = data; //copy data
            if (it != last) {
                ++it; //satisfy precondition of traverse tree "function must handle updating location between calls"
            }
        };

    //copy data back to original container
    traverseTree(head, copyOut);
    
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED

