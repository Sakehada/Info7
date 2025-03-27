#ifndef GAME_HPP
#define GAME_HPP
#include "world.hpp"
#include "window.hpp"

struct Game
{
    World *world;
    const SDL_Color Empty = {0, 0, 0, 255};
    const SDL_Color Border = {190, 190, 190, 255};
    const SDL_Color Lose = {0, 0, 190, 255};
    const SDL_Color Type1 = {255, 0, 0, 255};
    const SDL_Color Type2 = {0, 255, 0, 255};
    int racket_y;
    int racket_x;
    int racket_half_width;
    const SDL_Color racket_color = {0, 0, 250, 255};
};
void init_game(Game *game, string filename);
void display_game(Window *window, Game *game);
#endif