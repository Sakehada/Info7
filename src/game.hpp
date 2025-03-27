#ifndef GAME_HPP
#define GAME_HPP
#include "world.hpp"
#include "window.hpp"

enum Statut{
    Begin,
    Play,
    Pause,
    Win,
    GameOver
};

struct Game
{
    World *world;
    Statut statut{Begin};
    int direction[2];
    const SDL_Color colors[5] = {{0, 0, 0, 255}, {190, 190, 190, 255}, {0, 0, 190, 255}, {255, 0, 0, 255}, {0, 255, 0, 255}};
    int racket_y;
    int racket_x;
    int racket_half_width;
    const SDL_Color racket_color = {0, 0, 250, 255};
    int ball_speed;
    int ball_x, ball_y;
    int ball_dx, ball_dy;
};
void init_game(Game *game, string filename);
void display_game(Window *window, Game *game);
void move_ball(Game* game);
void change_statut(Statut* statut);
#endif