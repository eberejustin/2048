#include <iostream>
using namespace std;

#ifndef BOARD_H_  
#define BOARD_H_

class Board
{
public:
    Board(int x);
    //initializes tiles to NULL
    //creates an x by x 2D array of 0's
    // adds 2 at the top right and bottom left
    //sets board_size to x

    int move_tiles(char x);
    //takes in a character input as direction
    //moves all tiles to the end of the specified direction
    //adds equal elements
    //moves all tiles to the end again
    //introduces a new number on board
    //calculates the score from specified move
    //returns the score from that move

    void display();
    //displays the board

    bool is_full();
    //true if board is full
    //false if not

    bool adjacent_equals();
    //true if there are adjacent equal numbers in the board
    //false if not
    
    ~Board();
    //destructor for board

    //functions below should be private but spec says all should be public so..
    void move_to_end(char direc);
    //helper for move_tiles, moves all tiles to the end of specified dirction

    int add_equals(char direc);
    //helper for move_tiles, adds adjacent equal numbers

    void add_new();
    //helper for move_tiles, adds a new number on board

    void swap(int &x, int &y);
    //helper for move_to_end
    //swaps value of two characters

private:    
    int **tiles;
    //2D array that stores the board
    
    int board_size;
    //stores the board size
    bool was_moved;
    //true if tiles moved during the round or remained the same
};

#endif