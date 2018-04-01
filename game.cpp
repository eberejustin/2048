#include <iostream>
#include <fstream>
#include <iomanip>
#include "game.h"
using namespace std;

Game::Game(int board_size): score(0), Board2048(board_size)
{
    //read scores from file
    high_scores.open("scores.txt");
    if(high_scores.is_open())
    {
        string temp;
        int temp2;

        while( high_scores >> temp >> temp2 )
        {
            if(temp != "-1")
            {
                names.push_back(temp);
                scores.push_back(temp2);
            }
        }
    }
    high_scores.close();
}

void Game::display()
{
    //display boars at top left corner of terminal
    cout << "\033[2J";
    cout << "\033[2;2H";
    flush(cout);

    //only show high score if a high score exists
    if(!scores.empty())
    {
        cout << "High Score: ";
        if(score <= scores[0])
            cout << scores[0];
        else
            cout << score; 
    }

    cout << "   Your Score: " << score << endl;

    Board2048.display();

    //reset terminal color to default
    cout << "\033[0m";
}

bool Game::is_allowed(char x)
{
    for (size_t i = 0; i < allowed.length(); ++i)
    {
        if (x == allowed[i])
            return true;
    }
    return false;
}

void Game::play_round(char direc)
{
    score += Board2048.move_tiles(direc);
}

bool Game::game_over()
{
    return Board2048.is_full() && !Board2048.adjacent_equals();
}
void Game::game_end()
{
    cout << "Game Over! That was a good game\n"
         << "What is your name? ";
    set_high_name();
    write_high_scores();
    display_high_scores();
}

void Game::set_high_name()
{
    cin.ignore();
    getline(cin, high_name);
}

void Game::write_high_scores()
{
    if(!scores.empty())
    //add scores at sorted position
    {
        vector<int>::iterator it;
        int first_score = scores.front();
        int last_score = scores.back();

        if( score < last_score )
        {
            scores.push_back(score);
            names.push_back(high_name);
        }
        else if( score > first_score )
        {
            scores.insert(scores.begin(),  score);
            names.insert(names.begin(), high_name);
            cout << "New High Score!!\n" << endl;
        }
        else 
        {
            for (it = scores.begin(); it != scores.end()-1; it++)
            {
                int first = *it, second = *(it+1);
                if(score < first && score > second)
                {
                    scores.insert (it+1, score);
                    int index = it+1 - scores.begin();
                    names.insert ((names.begin()+index), high_name);
                    break;
                }
            }
        }
    }
    else //if scores is empty i.e no previous high scores exist
    {
        scores.push_back(score);
        names.push_back(high_name);
    }

    high_points.open("scores.txt");
    high_points.setf(ios::left);
    for (size_t i = 0; i < scores.size(); ++i)
    {
        high_points << setw(15) << names[i] << " " << scores[i] << endl;
    }
    high_points << "-1";
    high_points.close();
}

void Game::display_high_scores()
{
    size_t index = 0;
    cout.setf(ios::left);
    if(!scores.empty())
    {
        while(index < 5 && index < scores.size())
        {
            cout << setw(15) << names[index] << " " << scores[index] << endl;
            index++;
        }
    }
    else
        cout << "No High Scores Yet\n";
}
