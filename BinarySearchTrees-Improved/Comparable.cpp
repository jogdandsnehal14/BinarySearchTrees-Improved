//---------------------------------------------------------------------------
// File: Comparable.cpp
// Author: Snehal Jogdand
// Date: 01/14/2020
// Program 1: Improved binary search trees
//
// DESCRIPTION:
// SearchTree: 
//  The class file for Comparable class
//  Provides the set of variables and functions to process 
//  a Comparable
//---------------------------------------------------------------------------

#include "Comparable.h"
#include <iostream>
#include <istream>

/** Overload << operator.
	 @pre None.
	 @param output The output stream to print the output
	 @param item The Comparable object to output
 */
ostream& operator<<(ostream& output, Comparable& item)
{
	output << item.data;
	return output;
}

/** Overload >> operator.
	 @pre None.
	 @param output The input stream to get the input
	 @param item The Comparable object to input value to
 */
istream& operator>>(istream& input, Comparable& item)
{
	char chr;
	input >> chr;
	item.data = chr;
	
	return input;
}

/** Overload equality check operator.
	 @pre None.
	 @param right The SearchTree object to compare against
	 @returns True if the two tree are equal
 */
bool Comparable::operator==(Comparable const& right)
{
	return data == right.data;
}

/** Overload not equality check operator.
	 @pre None.
	 @param right The SearchTree object to compare against
	 @returns True if the two tree are not equal
 */
bool Comparable::operator!=(Comparable const& right)
{
	return data != right.data;
}

/** Overload < operator.
	 @pre None.
	 @param right The SearchTree object to compare against
	 @returns True if the comparable object is less than the right
 */
bool Comparable::operator<(Comparable const& right)
{
	return data < right.data;
}

/** Overload > operator.
	 @pre None.
	 @param right The SearchTree object to compare against
	 @returns True if the comparable object is greater than the right 
 */
bool Comparable::operator>(Comparable const& right)
{
	return data > right.data;
}
