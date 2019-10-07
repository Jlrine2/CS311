// counthar.cpp
// 2019-10-07
// James Rine
// For CS 311 Fall 2019
// source for CountHar

#include <vector>
using std::vector;

//wrap x and y values to allow for less parameter passing
struct position{
    int x;
    int y;

    position(int x, int y): x(x), y(y){}
};

//compare two positions on the board.
bool operator==(const position & lhs, const position & rhs){
    return rhs.x == lhs.x && lhs.y ==rhs.y;
}

//workhorse function for countHAR
int countHAR_recurse(vector< vector< int >> & board,
                    const position & ant, 
                    const position & finish,
                    const int dim_x, const int dim_y,
                    int & remaining){

    //BASE CASES

    //check if on board
    if (0 > ant.y || ant.y >= dim_y || 0 > ant.x || ant.x >= dim_x) return 0;
    
    //check if ant has already been to this position
    if (board[ant.x][ant.y] == 1) return 0;

    //define this position
    board[ant.x][ant.y] = 1;
    --remaining;

    //check for full solution
    if (remaining == 0 &&
        ant == finish){
            //undo changes to board state
            ++remaining;
            board[ant.x][ant.y] = 0;
            return 1;
        }

    //RECUSIVE CASE

    //recursivly calulate number of holey ant runs from each position N/S/E/W
    int total =     countHAR_recurse(board, position(ant.x - 1, ant.y), finish, dim_x, dim_y, remaining) 
                  + countHAR_recurse(board, position(ant.x + 1, ant.y), finish, dim_x, dim_y, remaining) 
                  + countHAR_recurse(board, position(ant.x, ant.y - 1), finish, dim_x, dim_y, remaining)
                  + countHAR_recurse(board, position(ant.x, ant.y + 1), finish, dim_x, dim_y, remaining);
    
    //undo changes to board state.
    ++remaining;
    board[ant.x][ant.y] = 0;
    return total;
}



//count number of possible solutions to the holey and run problem
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
            int finish_x, int finish_y){


                //define board as vector of vector
                vector< vector< int > > board(dim_x, vector< int >(dim_y,0));

                //define position of hole
                board[hole_x][hole_y] = 1;

                //define amount of places to goto
                int remaining = (dim_y *dim_x) - 1;

                return countHAR_recurse(board, position(start_x, start_y), position(finish_x, finish_y), dim_x, dim_y, remaining);

    }