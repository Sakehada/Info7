// Jules Grenesche
// Séance 1 info7

// include
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include "../../src/window.hpp"
#include "../../src/world.hpp"
#include "../../src/include/SDL2/SDL.h"
#include <fstream>

using namespace std;
struct Ball
{
    int x;
    int y;
    int dx;
    int dy;
};
// fonction

void echiquier(Window *window, int lig, int col, SDL_Color couleur1, SDL_Color couleur2) // fonction
{
    set_color(&window->background, &couleur1); // couleur 1
    set_color(&window->foreground, &couleur2); // couleur 1
    clear_window(window);
    int x, y, w, h;

    for (int i = 0; i < col; i++)
    {
        for (int k = 0; k < lig; k++)
        {
            // x= i * 600/lig
            // y= k * 1000/col
            // w= (i+1) * 600/lig
            // h=(k+1)* 1000/lig
            if (i + k == 0 || (i + k) % 2 == 0) // on desine un rectangle si les coordonnes sont pairs
            {
                w = int(window->width / col);
                h = int(window->height / lig);
                x = i * w;
                y = k * h;
                draw_fill_rectangle(window, x, y, w, h);
            }
        }
    }
}

void dessine_pentominos(Window *window) // desine un pentominos
{
    set_color(&window->background, 255, 165, 0, 150); // couleur orange pour faire la derniere figure
    set_color(&window->foreground, 255, 0, 255, 150); // couleur Violet pour les dessins
    clear_window(window);
    int w = int(window->width / 5);  // largeur d un rectangle
    int h = int(window->height / 5); // hauteur ///
    // on dessine la forme violette
    draw_fill_rectangle(window, 0, 0, 2 * w, h);
    draw_fill_rectangle(window, 0, 0, h, 3 * h);
    draw_fill_rectangle(window, 0, 2 * h, 2 * w, h);
    set_color(&window->foreground, 0, 255, 0, 150); // on change la couleur en vert et on dessine la forme de la meme couleur ect ect
    draw_fill_rectangle(window, 0, 3 * h, 2 * w, 2 * h);
    draw_fill_rectangle(window, 2 * w, 3 * h, w, h);
    set_color(&window->foreground, 255, 192, 203, 150); // on change la couleur en rose
    draw_fill_rectangle(window, 2 * w, 4 * h, 3 * w, 1 * h);
    draw_fill_rectangle(window, 3 * w, 2 * h, w, 3 * h);
    set_color(&window->foreground, 0, 0, 255, 150); // on change la couleur en rose
    draw_fill_rectangle(window, 3 * w, 0, 2 * w, h);
    draw_fill_rectangle(window, 4 * w, 0, w, 4 * h);
}

void mouvement_balle(Ball *balle) // bouge la balle en fonction de ses parametres
{
    switch (balle->x)
    {
    case 0: // si sur le bord gauche
        balle->dx = balle->dx * (-1);
        break;

    case 800 - 20: // limite de la window - la taille de texture
        balle->dx = balle->dx * (-1);
        break;

    default:
        break;
    }
    switch (balle->y)
    {
    case 0: // si sur le bord haut
        balle->dy = balle->dy * (-1);
        break;

    case 600 - 20: // limite de la window - la taille de texture
        balle->dy = balle->dy * (-1);
        break;

    default:
        break;
    }

    balle->x = balle->x + balle->dx; // on avance la balle en fonction de son sens
    balle->y = balle->y + balle->dy;
}

int WinMain(int argc, char **argv)
{
    World world;
    Block b;
    b = Border;
    init_world(&world, 10, 11);
    write(&world, 11, 11, b);
    display(&world);
    return 0;
}