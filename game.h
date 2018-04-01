#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "board.h"
using namespace std;

#ifndef GAME_H_  
#define GAME_H_

class Game
{
public:
    Game(int board_size);
    //constructor for game class
    //constructs board with board_size
    //initializes score to 0
    //opens high score file and reads scores into scores vector

    void display_high_scores();
    //displays the top 5 high scores

    void write_high_scores();
    //writes the high scores into high score file

    void set_high_name();
    //gets name of user for high score file

    bool game_over();
    //is the game_over
    //check for adjacent equals and full board
    //returns value of game_over

    static bool is_allowed(char x);
    //checks if a character input is allowed for the game
    //true if allowed, false if not

    void game_end();
    //gets the name of the player, 
    //adds his/her/their name to the highscore file
    //displays the new top 5 high scores.

    void play_round(char direc);
    //moves tiles and adds em up using board.move_tiles()
    //adds score from round to overall score

    void display();
    //displays the game space(Your Score: ### High Score: ####) and board

private:
    int score;
    //stores the score of the user

    Board Board2048;
    //initializes the board object

    string high_name;
    //name of user who just played

    ifstream high_scores;
    //reads scores from high score file

    ofstream high_points;
    //writes scores to the high score file

    vector<int> scores;
    //stores all the high scores from file

    vector<string> names;
    //stores all the names from file

    static string allowed;
    //allowed imput characters
};


#endif