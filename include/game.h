#pragma once
#ifndef LCODE_GAME_H
#define LCODE_GAME_H

namespace LCode
{

class Game
{
    char key;
    int cursor_y, cursor_x, screen_y, screen_x;
    unsigned short count;
    bool running, ran;

public:
    Game();
    int run();
    ~Game();

private:
    // These are ran once at the beginning and ending of run()
    void run_begin();
    void run_end();

    // These are part of the game run loop
    void events();      // gather input & game events
    void update();      // update game logic 1 tick of time, responding to events
    void draw();        // draw to the screen
    void post_update(); // prepare data for next frame update after draw
};

} // namespace LCode


#endif // LCODE_GAME_H