// dp3.cpp 
// James Rine
// 2019-09-30
//
// For CS 311 Fall 2019
// Header for Project 3 Functions

//This file is based of off dp3.cpp written by Glen Chappel:
//    https://projects.cs.uaf.edu/redmine/projects/cs311_2019_03/repository/changes/dp3.cpp

#include "dp3.h"       // For Project 3 prototypes & templates

#include <functional>
using std::function;

// didItThrow will trow the same exception as the function passed. 
// sets threw based on exceptions
void didItThrow(const function<void()> & ff,
                bool & threw)
{
    threw = false;
    try {
        ff();
    }
    catch (...){
        threw = true;
        throw; //throw same exception   
    }
}

// recursive function to find greatest common denominator between two numbers.
// PreConditions:
// a and b must be non negitive
int gcd(int a,
        int b)
{
    if ( a == 0) return b;

    if (a > b){
        return gcd(b, a);
    }
    return (gcd(b % a, a));
}

