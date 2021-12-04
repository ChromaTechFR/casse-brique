#include "utils.h"
#include <stdlib.h>

Game genBlocks() {
    Game game = malloc(sizeof(struct GameStruct));
    //initialise les variables
    game->score = 0;
    //la barre
    game->barre.x = GetScreenWidth()/2;
    game->barre.y = GetScreenHeight()-30;
    game->barre.width = 100; 
    game->barre.height = 20;
    //la balle
    game->balle.x = GetScreenWidth()/2;
    game->balle.y = GetScreenHeight()-100;
    //la vélocité de la balle
    game->ballevitesse.x = 3;
    game->ballevitesse.y = -3;
    //la taille de la balle
    game->tailleballe = 10.0f;
    //génère le tableau de blocks avec la vie
    int i;
    for(i=0; i<8; i++) {
        int a;
        for(a=0; a<12; a++) {
            switch (i) {
                case 0: game->blocks[i][a] = 4; break;
                case 1: game->blocks[i][a] = 4; break;
                case 2: game->blocks[i][a] = 3; break;
                case 3: game->blocks[i][a] = 3; break;
                case 4: game->blocks[i][a] = 2; break;
                case 5: game->blocks[i][a] = 2; break;
                case 6: game->blocks[i][a] = 1; break;
                case 7: game->blocks[i][a] = 1; break;
            }
        }
    }
    return game;
}

void events(Game game) {
    if(IsKeyDown(KEY_LEFT) && game->barre.x > 40) { // on déplace la barre à gauche
            game->barre.x -= 10;
        }
        if(IsKeyDown(KEY_RIGHT) && game->barre.x < GetScreenWidth()-132) { // on déplace la barre à droite
             game->barre.x += 10;
        } //on déplace la barre à droite
}

void ballpos(Game game, Rectangle ballerec) {
    if(game->balle.x < (0 + ballerec.width)) {game->ballevitesse.x = game->ballevitesse.x * -1;}
    if(game->balle.x > (GetScreenWidth() - ballerec.width)) {game->ballevitesse.x = game->ballevitesse.x * -1;}
    if(game->balle.y < (0 + ballerec.width)) game->ballevitesse.y = game->ballevitesse.y * -1;
    game->balle.x += game->ballevitesse.x;
    game->balle.y += game->ballevitesse.y;
}

Color getRectangleColor(int vie) {
    Color couleur = BLACK;
    //choisis la couleur en fonction de la vie
    switch (vie) {
        case 1: couleur = GREEN; break;
        case 2: couleur = YELLOW; break;
        case 3: couleur = ORANGE; break;
        case 4: couleur = MAGENTA; break;
    }
    return couleur;
}

void blockWorker(Game game, Rectangle ballerec) {
    int i;
    
    for(i=0; i<8; i++) {
        int a;
        for(a=0; a<12; a++) {
            if(game->blocks[i][a] > 0) {
                //calcul la position du rectangle
                Rectangle rectangle = {85*a, 50*i, 85, 50};
                //calcule la colision avec une balle
                bool colision = CheckCollisionRecs(rectangle, ballerec);
                if(colision) {
                    game->blocks[i][a]--;
                    game->ballevitesse.x = game->ballevitesse.x * -1;
                    game->ballevitesse.y = game->ballevitesse.y * -1;
                    game->score++;
                    if(game->ballevitesse.x > 0) game->ballevitesse.x += -5;
                    else game->ballevitesse.x += 5;
                    game->ballevitesse.x += 5; //ballevitesse.y--;
                    //printf("vitesse balle : %i\n", ballevitesse.x);
                }
                    //Desinne le rectangle
                Color couleur = getRectangleColor(game->blocks[i][a]);
                DrawRectangleRec(rectangle, couleur);
                DrawRectangleLinesEx(rectangle, 1, BLACK);
                //DrawRectangleLines(85*a, 50*i, 85, 50, BLACK);
            }
        }
    }
    ballpos(game, ballerec);
}