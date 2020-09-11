//---------------------------------------------------------------------------
// File: SearchTree.h
// Author: Snehal Jogdand
// Date: 01/14/2020
// Program 1: Improved binary search trees
//
// DESCRIPTION:
// SearchTree: 
//  The header file for SearchTree class
//  Provides the set of variables and functions to process 
//  a Binary Search Tree
//---------------------------------------------------------------------------

#ifndef SEARCH_TREE_
#define SEARCH_TREE_

//---------------------------------------------------------------------------
// SearchTree: The header file for SearchTree class
// Provides the set of variables and functions to process 
// a Binary Search Tree
//---------------------------------------------------------------------------

#include <string>
#include "Comparable.h"
#include <iostream>

using namespace std;

/**
    The Binary Search Tree Node structure
 */
struct Node
{
    Comparable* item;   // the comparable pointer
    int count;          // the sorting key count
    Node* left;         // left pointer
    Node* right;        // right pointer
};

/**
    The Binary Search Tree class
 */
class SearchTree
{
private:
    Node* root;

    Node* createNode(Comparable* comparable);
    void inorder(ostream& output, Node* root);
    Node* copy(const Node* other);
    bool isEqual(const Node* left, const Node* right);
    int height(const Node* node) const;
    Node* search(Node* node, const Comparable& item) const;
    bool deleteNode(Node*& root, const Comparable& item);
    void deleteRoot(Node*& root);
    void clear(Node* node);

public:
    SearchTree();
    SearchTree(const SearchTree& other);

    bool insert(Comparable* comparable);
    bool remove(const Comparable& comparable);
    void makeEmpty();
    const Comparable* retrieve(const Comparable& comparable) const;
    int height(const Comparable& comparable) const;

    SearchTree operator=(const SearchTree& right);
    bool operator== (const SearchTree& right);
    bool operator!= (const SearchTree& right);
    friend ostream& operator<<(ostream& output, SearchTree& searchTree);

    ~SearchTree();
};
#endif