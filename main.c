/*
        Casse Brique Raylib      
    Par Neil et Quentin en TT3
*/
#include <raylib.h>
#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

int main(void) {
    InitWindow(1024, 800, "Casse Brique");
    SetTargetFPS(60); 

    Game game = genBlocks();
    //TODO s'occuper du status (perdu, gagné, pause) BORDEL
    while (!WindowShouldClose()) {
        //on capte les évènements
        events(game);
        //on indique qu'on commence à dessiner
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //calcul les blocks
        Rectangle ballerec = {game->balle.x, game->balle.y, (int)game->tailleballe, (int)game->tailleballe};
        blockWorker(game, ballerec);
        
        //TODO calculer la balle en fonction de la barre
        if(CheckCollisionRecs(game->barre, ballerec)) {
            //ballevitesse.x = ballevitesse.x * -1;
            game->ballevitesse.y = game->ballevitesse.y * -1;
            //balle.x -= 2;
            game->balle.y = GetScreenHeight() - 50;
        }
        //dessine la barre et la balle
        DrawRectangleRec(game->barre, RED);
        DrawCircle(game->balle.x, game->balle.y, game->tailleballe, ORANGE);
        //Affiche le score
        char scoreTexte[100]; sprintf(scoreTexte, "Score : %i", game->score);
        DrawText(scoreTexte, 5,5,25, GRAY);
        //Affiche le game over si la balle quitte l'écran
        if(game->balle.y > GetScreenHeight()) DrawText("Game Over", 240, 300, 100, BLACK);
        EndDrawing();
    }
    //on détruit tout
    free(game);
    CloseWindow();
    return 0;
}