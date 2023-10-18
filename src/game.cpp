#include "game.h"

#include <ncurses.h>    // initscr, printw, etc...

#include <string>   // std::string, std::to_string
#include <cstdlib>  // EXIT_SUCCESS

namespace LCode
{

Game::Game()
: key{'\0'},
  cursor_y{-1}, cursor_x{-1},
  screen_y{-1}, screen_x{-1},
  count{0},
  running{false}, ran{false}
{
    // set the locale (allows Unicode)
    setlocale(LC_ALL, "");
    // initialize screen
    initscr();
    // disable TTY driver buffer of typed characters (get per character)
    cbreak();
    // disable echoing of typed characters
    noecho();
    // flushes the screen when getting interrupt signal (faster?)
    intrflush(stdscr, FALSE);
    // enable backspace, delete, and arrow keys
    keypad(stdscr, TRUE);
}

int Game::run()
{
    run_begin();
    while (running)
    {
        events();
        update();
        draw();
        post_update();
    }
    run_end();

    return EXIT_SUCCESS;
}

Game::~Game()
{
    // deallocates the screen
    endwin();
}

/******************************************************************************
 *                             PRIVATE METHODS                                *
 ******************************************************************************/

void Game::run_begin()
{
    //print to the screen
    printw("Hello World!\n");
    refresh();

    count = 0;
    running = true;
}

void Game::run_end()
{ }

void Game::events()
{
    getyx(stdscr, cursor_y, cursor_x);
    getmaxyx(stdscr, screen_y, screen_x);
    // wait for user input
    key = static_cast<char>(getch());
}

void Game::update()
{
    if (cursor_y >= screen_y - 1 && cursor_x > 0)
    {
        clear();
        cursor_y = 0;
    }
}

void Game::draw()
{
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
}

void Game::post_update()
{
    ++count;
    running = key != '\b';
}

} // namespace LCode
