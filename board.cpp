#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "board.h"
using namespace std;

Board::Board(int x) : board_size(x)
{
    tiles = NULL; //initializes tiles to NULL

    tiles = new int*[x];
    for(int i = 0; i < x; i++)
        tiles[i] = new int[x];

    for(int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
            tiles[i][j] = 0;
    }

    //add two at top left and bottom right corners
    tiles[0][0] = 2;
    tiles[x - 1][x - 1] = 2;
}

void Board::display()
{
    cout.setf(ios::right);
    for(int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; ++j)
        {
            //change colors
            if(tiles[i][j] >= 2048)
                cout << "\033[31m";            
            else if(tiles[i][j] >= 128 )
                cout << "\033[32m";
            else if(tiles[i][j] >= 16)
                cout << "\033[35m";
            else if(tiles[i][j] > 0)
                cout << "\033[33m";
            else if(tiles[i][j] == 0)
                cout << "\033[0m";

            if(tiles[i][j] == 0)
                cout << setw(8) << "x";
            if(tiles[i][j] > 0)
                cout << setw(8) << tiles[i][j];
        }
        cout << endl << endl << endl;
    }
    cout << endl;
}

Board::~Board()
{
    for (int i = 0; i < board_size; ++i)
    {
        delete [] tiles[i];
    }
    delete [] tiles;
}

int Board::move_tiles(char direc)
{
    was_moved = false;
    int round_score = 0;

    move_to_end(direc);
    round_score = add_equals(direc);
    move_to_end(direc);
    
    if(was_moved)
        add_new();

    return round_score;
}

void Board::add_new()
{
    if(!is_full())
    {
        int four_two = rand() % 10;
        int pos_one = rand() % board_size;
        int pos_two = rand() % board_size;
        bool is_added = false;

        while(!is_added)
        {
            if (tiles[pos_one][pos_two] == 0 && four_two < 9)
            {
                tiles[pos_one][pos_two] = 2;
                is_added = true;
            }
            else if(tiles[pos_one][pos_two] == 0 && four_two == 9)
            {
                tiles[pos_one][pos_two] = 4;
                is_added = true;
            }
            else
            {
                pos_one = rand() % board_size;
                pos_two = rand() % board_size;  
            }
        }
    }
}

void Board::move_to_end(char direc)
{
    switch(direc)
    {
        //moves all tiles up
        case 'w':
            for (int i = 0; i < board_size; i++)
            {
                int count = 0;
                for (int j = 0; j < board_size ; j++)
                {
                    if(tiles[j][i] != 0)
                    {
                        count++;
                        if(tiles[count -1][i] != tiles[j][i])
                            was_moved = true;
                        swap(tiles[count -1][i], tiles[j][i]);
                    }   
                }   
            }
            break;          

        //moves all tiles down
        case 's':
            for (int i = 0; i < board_size; ++i)
            {
                int count = 0;
                for (int j = board_size-1; j >= 0 ; j--)
                {
                    if(tiles[j][i] != 0)
                    {
                        count++;
                        if(tiles[board_size - count][i] != tiles[j][i])
                            was_moved = true;
                        swap(tiles[board_size - count][i],tiles[j][i]);
                    }   
                }   
            }
            break;

        //moves all tiles left
        case 'a':
            for (int i = 0; i < board_size; ++i)
            {
                int count = 0;
                for (int j = 0; j < board_size ; j++)
                {
                    if(tiles[i][j] != 0)
                    {
                        count++;
                        if(tiles[i][count -1] != tiles[i][j])
                            was_moved = true;
                        swap(tiles[i][count -1],tiles[i][j]);
                    }
                }   
            }
            break;

        //moves all tiles right
        case 'd':
            for (int i = 0; i < board_size; ++i)
            {
                int count = 0;
                for (int j = board_size-1; j >= 0 ; j--)
                {
                    if(tiles[i][j] != 0)
                    {
                        count++;
                        if(tiles[i][board_size - count] != tiles[i][j])
                            was_moved = true;
                        swap(tiles[i][board_size - count],tiles[i][j]);
                    }   
                }   
            }
            break;
    }
}

int Board::add_equals(char direc)
{
    int round_score = 0;
    switch(direc)
    {
        //adds equal tiles upward
        case 'w':
            for (int i = 0; i < board_size; ++i)
            {
                for (int j = 0; j < board_size - 1; j++)
                {
                    if(tiles[j][i] != 0 && tiles[j][i] == tiles[j+1][i])
                    {
                        tiles[j][i] += tiles[j+1][i];
                        tiles[j+1][i] = 0;
                        round_score += tiles[j][i];
                    }   
                }   
            }
            break;

        //adds equal tiles down
        case 's':
            for (int i = 0; i < board_size; ++i)
            {
                for (int j = board_size-1; j > 0 ; j--)
                {
                    if(tiles[j][i] != 0 && tiles[j][i] == tiles[j-1][i])
                    {
                        tiles[j][i] += tiles[j-1][i];
                        tiles[j-1][i] = 0;
                        round_score += tiles[j][i];
                    }
                }   
            }
            break;

        //add equal tiles left
        case 'a':
            for (int i = 0; i < board_size; ++i)
            {
                for (int j = 0; j < board_size - 1 ; j++)
                {
                    if(tiles[i][j] != 0 && tiles[i][j] == tiles[i][j+1])
                    {
                        tiles[i][j] += tiles[i][j+1];
                        tiles[i][j+1] = 0;
                        round_score += tiles[i][j];
                    }
                }   
            }
            break;

        //adds equal tiles right
        case 'd':
            for (int i = 0; i < board_size; ++i)
            {
                for (int j = board_size-1; j > 0 ; j--)
                {
                    if(tiles[i][j] != 0 && tiles[i][j] == tiles[i][j-1])
                    {
                        tiles[i][j] += tiles[i][j-1];
                        tiles[i][j-1] = 0;
                        round_score += tiles[i][j];
                    }   
                }   
            }
            break;
    }
    return round_score;
}

bool Board::is_full()
{
    bool zero_exists = false;
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            if(tiles[i][j] == 0)
                zero_exists = true;
        }
    }
    return !zero_exists;
}

bool Board::adjacent_equals()
{
    bool equals_exist = false;

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size - 1; ++j)
        {
            if(tiles[i][j] == tiles[i][j+1])
                equals_exist = true;
        }
    }

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size - 1; ++j)
        {
            if(tiles[j][i] == tiles[j+1][i])
                equals_exist = true;
        }
    }

    return equals_exist;
}


void Board::swap(int &x, int &y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}
