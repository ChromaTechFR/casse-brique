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

    int score = 0;
    int status = 0; //0 = en jeu; 1 = gagné; 2 = en pause
    Rectangle barre = {LONGUEUR_FENETRE/2, HAUTEUR_FENETRE-30, 100, 20};
    Vector2 balle = {LONGUEUR_FENETRE/2, HAUTEUR_FENETRE-100};
    Vector2 ballevitesse = {3,-3};
    float tailleballe = 10.0f;

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
        if(IsKeyDown(KEY_LEFT) && barre.x > 40) { // on déplace la barre à gauche
            barre.x -= 10;
        }
        if(IsKeyDown(KEY_RIGHT) && barre.x < LONGUEUR_FENETRE-132) { // on déplace la barre à droite
             barre.x += 10;
        } //on déplace la barre à droite
        //on indique qu'on commence à dessiner
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //on dessine les objets
        int carrerestant = 0;
        //dessine les blocs
        int i;
        Rectangle ballerec = {balle.x, balle.y, (int)tailleballe, (int)tailleballe};
        for(i=0; i<8; i++) {
            int a;
            for(a=0; a<12; a++) {
                if(blocks[i][a] > 0) {
                    carrerestant++;
                    //calcul la position du rectangle
                    Rectangle rectangle = {85*a, 50*i, 85, 50};
                    //calcule la colision avec une balle
                    bool colision = CheckCollisionRecs(rectangle, ballerec);
                    if(colision) {
                        blocks[i][a]--;
                        ballevitesse.x = ballevitesse.x * -1;
                        ballevitesse.y = ballevitesse.y * -1;
                        score++;
                        if(ballevitesse.x > 0) ballevitesse.x += -5;
                        else ballevitesse.x += 5;
                        ballevitesse.x += 5; //ballevitesse.y--;
                        printf("vitesse balle : %i\n", ballevitesse.x);
                    }

                    Color couleur = BLACK;
                    //choisis la couleur en fonction de la vie
                    switch (blocks[i][a]) {
                    case 1: couleur = GREEN; break;
                    case 2: couleur = YELLOW; break;
                    case 3: couleur = ORANGE; break;
                    case 4: couleur = MAGENTA; break;
                    }
                    DrawRectangleRec(rectangle, couleur);
                    DrawRectangleLinesEx(rectangle, 1, BLACK);
                    //DrawRectangleLines(85*a, 50*i, 85, 50, BLACK);
                }
            }
        }
        //Calcule la position de la balle
        if(balle.x < (0 + ballerec.width)) {ballevitesse.x = ballevitesse.x * -1;}
        if(balle.x > (GetScreenWidth() - ballerec.width)) {ballevitesse.x = ballevitesse.x * -1;}
        if(balle.y < (0 + ballerec.width)) ballevitesse.y = ballevitesse.y * -1;
        balle.x += ballevitesse.x;
        balle.y += ballevitesse.y;
        //TODO calculer la balle en fonction de la barre
        if(CheckCollisionRecs(barre, ballerec)) {
            //ballevitesse.x = ballevitesse.x * -1;
            ballevitesse.y = ballevitesse.y * -1;
            //balle.x -= 2;
            balle.y = GetScreenHeight() - 50;
            //inverse X en fonction de la position de la barre
            //if((barre.x + (barre.width/2)) > balle.x) printf("balle : %i", ballevitesse.x); //la balle est au mauvais endroit


        }
        //dessine la barre
        //DrawRectangle(positionBarre, HAUTEUR_FENETRE-30, 100, 20, RED);
        DrawRectangleRec(barre, RED);
        //Affiche la balle
        DrawCircle(balle.x, balle.y, tailleballe, ORANGE);
        //Affiche la position de la barre et de la balle
        /*char barrePoseTexte[600];
        sprintf(barrePoseTexte, "Position de la barre : %i\nPosition de la balle : %.6g;%.6g\n", barre.x, balle.x, balle.y);
        printf("carre restant : %i", carrerestant);
        DrawText(barrePoseTexte, 5, 720, 24, BLACK);*/
        //Affiche le score
        char scoreTexte[100]; sprintf(scoreTexte, "Score : %i", score);
        DrawText(scoreTexte, 5,5,25, GRAY);

        //Affiche le game over si perdu ou le texte si gagné
        if(balle.y > GetScreenHeight()) DrawText("Game Over", 240, 300, 100, BLACK);
        //printf("%f\n", balle.y);
        EndDrawing();
    }
    //on détruit tout
    CloseWindow(); // Close window and OpenGL context

    return 0;
}