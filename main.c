/*
        Casse Brique Raylib      
    Par Neil et Quentin en TT3
*/
#include "raylib.h"
#include "stdio.h"
#define HAUTEUR_FENETRE 800
#define LONGUEUR_FENETRE 1024


int main(void) {
    //création des objets
    InitWindow(LONGUEUR_FENETRE, HAUTEUR_FENETRE, "Casse Brique");
    SetTargetFPS(60);  
    int positionBarre = LONGUEUR_FENETRE/2;
    Vector2 balle = {50,50};

    int blocks[8][12]; //le block est caractérisé par ses points de vie
    //génère le tableau
    int i;
    for(i=0; i<8; i++) {
        int a;
        for(a=0; a<12; a++) {
            switch (i) {
                //TODO REFACTOR
                case 0: blocks[i][a] = 4; break;
                case 1: blocks[i][a] = 4; break;
                case 2: blocks[i][a] = 3; break;
                case 3: blocks[i][a] = 3; break;
                case 4: blocks[i][a] = 2; break;
                case 5: blocks[i][a] = 2; break;
                case 6: blocks[i][a] = 1; break;
                case 7: blocks[i][a] = 1; break;
            }
        }
    }
    //la boucle du jeu
    while (!WindowShouldClose()) {
        //on capte les évènements
        if(IsKeyDown(KEY_LEFT) && positionBarre > 40) { // on déplace la barre à gauche
            positionBarre -= 10;
        }
        if(IsKeyDown(KEY_RIGHT) && positionBarre < LONGUEUR_FENETRE-132) { // on déplace la barre à droite
             positionBarre += 10;
        } //on déplace la barre à droite
        //on indique qu'on commence à dessiner
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //on dessine les objets
        DrawRectangle(positionBarre, HAUTEUR_FENETRE-30, 100, 20, RED);
        //dessine les blocs
        int i;
        for(i=0; i<8; i++) {
            int a;
            for(a=0; a<12; a++) {
                if(blocks[i][a] > 0) {
                    Color couleur = BLACK;
                    //choisis la couleur en fonction de la vie
                    switch (blocks[i][a])
                    {
                    case 1: couleur = GREEN; break;
                    case 2: couleur = ORANGE; break;
                    case 3: couleur = GRAY; break;
                    case 4: couleur = MAGENTA; break;
                    }
                    DrawRectangle(85*a, 50*i, 85, 50, couleur);
                    DrawRectangleLines(85*a, 50*i, 85, 50, BLACK);
                }
            }
        }
        //Calcule la position de la balle
        //TODO calculer la balle
        //Affiche la balle
        DrawCircle(balle.x, balle.y, 10.0f, ORANGE);
        //Affiche la position de la barre et de la balle
        char barrePoseTexte[200];
        sprintf(barrePoseTexte, "Position de la barre : %i\nPosition de la balle : %.6g;%.6g", positionBarre, balle.x, balle.y);
        DrawText(barrePoseTexte, 5, 720, 24, BLACK);
        
        EndDrawing();
    }
    //on détruit tout
    CloseWindow();        // Close window and OpenGL context

    return 0;
}