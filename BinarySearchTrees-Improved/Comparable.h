//---------------------------------------------------------------------------
// File: Comparable.h
// Author: Snehal Jogdand
// Date: 01/14/2020
// Program 1: Improved binary search trees
//
// DESCRIPTION:
// SearchTree: 
//  The header file for Comparable class
//  Provides the set of variables and functions to process 
//  a Comparable
//---------------------------------------------------------------------------

#ifndef COMPARABLE_
#define COMPARABLE_

//---------------------------------------------------------------------------
// Comparable: The header file for Comparable class
// Provides the set of variables and functions to process 
// a Comparable
//---------------------------------------------------------------------------

#include <string>

using namespace std;

class Comparable
{
private:
    char data;

public:
    bool operator== (Comparable const& right);
    bool operator!= (Comparable const& right);
    bool operator< (Comparable const& right);
    bool operator> (Comparable const& right);
    friend ostream& operator<<(ostream& output, Comparable& item);
    friend istream& operator>>(istream& input, Comparable& item);
};
#endif