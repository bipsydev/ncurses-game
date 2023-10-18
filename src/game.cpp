#include "game.h"

#include <ncurses.h>    // initscr, printw, etc...

#include <string>   // std::string, std::to_string
#include <cstdlib>  // EXIT_SUCCESS

LCode::Game::Game()
{
    // initialize screen
    initscr();
    // disable TTY driver buffer of typed characters (get per character)
    cbreak();
    // disable echoing of typed characters
    noecho();
    // enable backspace, delete, and arrow keys
    keypad(stdscr, TRUE);
}

int LCode::Game::run()
{
    //print to the screen
    printw("Hello World!\n");
    refresh();

    char key;
    int cursor_y, cursor_x, screen_y, screen_x;
    unsigned short count = 0;
    do
    {
        getyx(stdscr, cursor_y, cursor_x);
        getmaxyx(stdscr, screen_y, screen_x);
        // wait for user input
        key = static_cast<char>(getch());
        if (cursor_y >= screen_y - 1 && cursor_x > 0)
        {
            clear();
            cursor_y = 0;
        }
        std::string message = "You pressed \"" + std::string{key} + "\" ("
                            + std::to_string(static_cast<int>(key)) + ") !";
        printw(message.c_str());

        printw((" line = " + std::to_string(cursor_y)).c_str());
        printw((" / " + std::to_string(screen_y - 1)).c_str());

        printw("\n");
        if (count == 5)
        {
            printw("Press Backspace when you want to exit the program.\n");
        }
        refresh();
        ++count;
    }
    while (key != '\b' /* backspace */);

    return EXIT_SUCCESS;
}

LCode::Game::~Game()
{
    // deallocates the screen
    endwin();
}
