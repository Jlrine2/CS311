// counthar.h
// 2019-10-07
// James Rine
// For CS 311 Fall 2019
// Header for CountHar




//include gaurds
#ifndef COUNTHAR_H_INCLUDED
#define COUNTHAR_H_INCLUDED


// defined in souce file
//  count number of possible solutions to the holey and run problem
//  passed 8 parameters:
//    First and second are x and y dimentions of board respectively
//    3rd and 4th are (x,y) coordinates of hole respectively
//    5th and 6th are (x,y) coordinates of starting position respectivly
//    7th and 8th are (x,y) coordingates of ending position respectively
//
//PreConditions:
// all parameters must be positive integers
// all coordinate values must be in range of specified board size
int countHAR(int dim_x, int dim_y,
            int hole_x, int hole_y,
            int start_x, int start_y,
            int finish_x, int finish_y);

#endif