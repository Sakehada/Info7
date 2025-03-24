#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
using namespace std;

enum Block
{
    Empty,
    Border,
    Type1,
    Type2,
    Lose

};

struct World
{
    int width;
    int height;
    Block *grid;
};

void init_world(World *world, int w, int h);
void free_world(World *world);
Block read(World *world, int x, int y);
void write(World *world, int x, int y, Block b);
void display(World *world);
#endif