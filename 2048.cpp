#include <ctime>
#include <ncurses.h>
#include <cstdlib>
#include <cctype>
#include "game.h"
using namespace std;

string Game::allowed = "wasdhq";

int main()
{
    int board_size = 0; 
    char direc;

    //seed the random variables
    srand(time(NULL));

    cout << "Welcome to the amazing world of 2's! \n"
         << "Combine the numbers till you can't do it anymore\n\n"
          << "use the arrow keys to move tiles\n"
         << "q to quit\n"
         << "h to view high scores\n\n";

    cout << "What board size do you want to play with?(between 2 and 10) ";
    do
    {
        cin >> board_size;
        if(cin.fail() || board_size < 2 || board_size > 10)
        {
            cout << "Please enter a valid board size: ";
            cin.clear();
            cin.ignore(); 
        }
    }
    while( cin.fail() || board_size < 2 || board_size > 10 );

    Game Game2048(board_size);
    Game2048.display();
    // start curses mode
    initscr();
    while(!Game2048.game_over())
    {
        direc = getch();
        switch(direc)
        {
            case KEY_UP: 
                direc = 'w';
                break;
            case KEY_DOWN: 
                direc = 's';
                break;
            case KEY_RIGHT: 
                direc = 'd';
                break;
            case KEY_LEFT: 
                direc = 'a';
                break;
        }
        if(Game::is_allowed(direc))
        {
            if(direc == 'q')
                break;
            else if(direc == 'h')
                Game2048.display_high_scores();
            else
            {
                Game2048.play_round(direc);
                Game2048.display();
            }
        }
        refresh();
    }

    Game2048.game_end();
    refresh();
    endwin();
    return 0;
}
