//---------------------------------------------------------------------------
// File: SearchTree.cpp
// Author: Snehal Jogdand
// Date: 01/14/2020
// Program 1: Improved binary search trees
//
// DESCRIPTION:
// SearchTree: 
//  The class file for SearchTree class
//  Provides the set of variables and functions to process 
//  a Binary Search Tree
//---------------------------------------------------------------------------

#include "SearchTree.h"
using namespace std;

/**
    The binary search tree default constructor
  */
SearchTree::SearchTree() : root(nullptr)
{
}

/** The copy constructor for binary search tree
    @pre None.
    @param other The binary search tree to copy from
 */
SearchTree::SearchTree(const SearchTree& other)
{
    root = copy(other.root);
}

/** The copy helper for binary search tree
    @pre None.
    @param other The binary search tree to copy from
 */
Node* SearchTree::copy(const Node* other)
{
    if (other == nullptr) return nullptr;

    Node* node = createNode(other->item);
    node->left = copy(other->left);
    node->right = copy(other->right);
    node->count = other->count;

    return node;
}

/** Checks if the two binary search tree are equal
    @pre None.
    @param node1 The root of binary search tree 1
    @param node2 The root of binary search tree 2
    @returns true if the two binary search tree are equal, false otherwise
 */
bool SearchTree::isEqual(const Node* node1, const Node* node2)
{
    if (node1 == nullptr && node2 == nullptr) return true;
    else if (node1 != nullptr && node2 == nullptr) return false;
    else if (node1 == nullptr && node2 != nullptr) return false;
    else if (*node1->item == *node2->item && node1->count == node2->count)
        return isEqual(node1->left, node2->left)
        && isEqual(node1->right, node2->right);

    return false;
}

/** Creates a new node with the given comparable item
    @pre None.
    @param item The comparable item
    @returns The newly created Node object
 */
Node* SearchTree::createNode(Comparable* item)
{
    Node* node = new Node;
    node->item = item;
    node->count = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

/** Iteratively inserts a Comparable into the tree or increments the count
    if it is already in the tree. This method returns false if the
    Comparable is found (and, thus, not inserted).
    @pre None.
    @param item The comparable item
    @returns True if the new item is inserted
 */
bool SearchTree::insert(Comparable* item)
{
    // empty tree - set the root node
    if (root == nullptr)
    {
        root = createNode(item);
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;

    // find the position where the node can be inserted
    while (current != nullptr)
    {
        parent = current;
        if (*(current->item) > * item)
            current = current->left;
        else if (*(current->item) < *item)
            current = current->right;
        else
        {
            // duplicate node found, just increment the count and return
            current->count++;
            return false;
        }
    }

    Node* node = createNode(item);
    if (*(parent->item) > * item)
        parent->left = node;
    else if (*(parent->item) < *item)
        parent->right = node;

    return true;
}

/** Removes one occurrence of a Comparable from the tree. If it is the last
    occurrence, remove the node. Return false if the Comparable is not found.
    @pre None.
    @param item The comparable item
    @returns True if item is removed, false otherwise
 */
bool SearchTree::remove(const Comparable& item)
{
    return deleteNode(root, item);
}

/** Removes and deallocates all of the data from the tree.
    @pre None.
 */
void SearchTree::makeEmpty()
{
    clear(root);
    delete root;
    root = nullptr;
}

/** Finds a Comparable in the tree using a key stored in the parameter.
    @pre None.
    @param item The comparable item
    @returns The comparable item found, nullptr if not found
 */
const Comparable* SearchTree::retrieve(const Comparable& item) const
{
    // get the node in the tree
    Node* node = search(root, item);

    // node found, return the corresponding item
    if (node != nullptr) return node->item;

    // no node found, return null
    return nullptr;
}

/** Returns the height of the node storing the Comparable in the tree.
    A leaf has height 0. Return -1 if the Comparable is not found.
    @pre None.
    @param item The comparable item
    @returns The height of the tree
 */
int SearchTree::height(const Comparable& item) const
{
    Node* node = search(root, item);

    // item not found, return -1
    if (node == nullptr) return -1;

    return height(node);
}

/** Returns the height of the node storing the Comparable in the tree.
    A leaf has height 0. Return -1 if the Comparable is not found.
    @pre None.
    @param node The root node
    @returns The height of the tree
 */
int SearchTree::height(const Node* node) const
{
    if (node == nullptr) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

/** Searches a Comparable in the tree using the comparable item stored in the parameter.
    @pre None.
    @param node The root node
    @param item The comparable item
    @returns The node with comparable item found, nullptr if not found
 */
Node* SearchTree::search(Node* node, const Comparable& item) const
{
    if (node == nullptr) return nullptr;
    else if (*node->item == item)
        return node;
    else if (*(node->item) > item)
        return search(node->left, item);
    else
        return search(node->right, item);
}

/** Deletes a Node in the tree which has the the comparable item in the parameter.
    @pre None.
    @param node The root node
    @param item The comparable item
    @returns True if deletion succeeds, false otherwise
 */
bool SearchTree::deleteNode(Node*& root, const Comparable& item)
{
    if (root == nullptr) return false;
    else if (*root->item == item)
    {
        if (root->count > 1)
            root->count--;
        else
            deleteRoot(root);

        return true;
    }
    else if (*root->item > item)
        return deleteNode(root->left, item);
    else
        return deleteNode(root->right, item);

    return false;
}

/** Deletes the root node in the tree
    @pre None.
    @param node The root node
 */
void SearchTree::deleteRoot(Node*& root)
{
    delete root->item;

    // leaf node
    if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        root = nullptr;
    }
    // node with one child
    else if (root->left == nullptr || root->right == nullptr)
    {
        Node* tmp = root;
        root = root->left == nullptr ? root->right : root->left;
        delete tmp;
    }
    // node with both children
    else
    {
        // get max from left subtree 
        Node* parent = root->right;
        Node* maxLeft = root->right;
        while (maxLeft->left != nullptr)
        {
            parent = maxLeft;
            maxLeft = maxLeft->left;
        }

        parent->left = maxLeft->right;

        // copy max values to the root node
        root->item = maxLeft->item;
        root->count = maxLeft->count;

        delete maxLeft;
    }
}

/** Overload assignment operator.
    @pre None.
    @param other The SearchTree object to copy values from
    @returns The SearchTree object
 */
SearchTree SearchTree::operator=(SearchTree const& other)
{
    if (&other != this)
    {
        SearchTree temp(other);
        swap(temp.root, root);
    }

    return *this;
}

/** Overload equality check operator.
    @pre None.
    @param right The SearchTree object to compare against
    @returns True if the two tree are equal
 */
bool SearchTree::operator==(const SearchTree& right)
{
    return isEqual(root, right.root);
}

/** Overload not equality check operator.
    @pre None.
    @param right The SearchTree object to compare against
    @returns True if the two tree are not equal
 */
bool SearchTree::operator!=(const SearchTree& right)
{
    return !isEqual(root, right.root);
}

/** Overload << operator.
    @pre None.
    @param output The output stream to print the output
    @param searchTree The SearchTree object to output
 */
ostream& operator<<(ostream& output, SearchTree& searchTree)
{
    searchTree.inorder(output, searchTree.root);
    return output;
}

/** Prints the inorder traversal of the search tree
    @pre None.
    @param output The output stream to print the output
    @param node The root node
 */
void SearchTree::inorder(ostream& output, Node* node)
{
    if (node == nullptr) return;
    inorder(output, node->left);
    output << *node->item << "\t" << node->count << endl;
    inorder(output, node->right);
}

/**
 * Destroys all the nodes in the given BS Tree in a recursive manner
 */
void SearchTree::clear(Node* node)
{
    Node* nodeToDeletePtr = node;

    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr)
    {
        // Return node to the system
        /*
        if (nodeToDeletePtr->item != nullptr)
        {
            delete nodeToDeletePtr->item;
            nodeToDeletePtr->item = nullptr;
        }
        */

        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        return;
    }

    clear(node->left);
    clear(node->right);

    nodeToDeletePtr->left = nullptr;
    nodeToDeletePtr->right = nullptr;
}

/**
    The Search Tree destructor
 */
SearchTree::~SearchTree()
{
    clear(root);
    delete root;
    root = nullptr;
}