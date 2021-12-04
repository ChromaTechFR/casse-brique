#ifndef UTILS_H
#define UTILS_H
#include <raylib.h>

struct GameStruct {
    int blocks[8][12];
    int score;
    Rectangle barre;
    Vector2 balle;
    Vector2 ballevitesse;
    float tailleballe;
}; typedef struct GameStruct* Game;

Game genBlocks();

void events(Game game);
void ballpos(Game game, Rectangle ballerec);
Color getRectangleColor(int vie);

void blockWorker(Game game, Rectangle ballerec);
#endif