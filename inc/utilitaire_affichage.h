/******************************************************************************/
/*  UTILITAIRE_AFFICHAGE.H                                                    */
/*  Module utilitaire qui permet d'afficher les cases d'une grille en mode    */
/*  graphique avec le module graphique "winBGim.h".                           */
/*                                                                            */
/*  Conception : Pierre Bélisle, Eric Thé                                     */
/******************************************************************************/

#ifndef utilitaire_affichage_h
#define utilitaire_affichage_h  1

#include "winbgim.h"

//Permet de travailler avec une fenêtre graphique de la dimension demandée.
//Reçoit les dimensions de la grille (le nombre de "cases" désirées).
//NOTE: utilisez la fonction "void initwindow(int nb_pixels_X, int nb_pixels_Y);"
void init_graphe(int nb_cases_lignes, int nb_cases_colonnes);

//Permet de dessiner un cadre autour de la zone d'affichage (reçoit les dimensions de la grille)
void init_zone_environnement(int dimy, int dimx);

//Affiche le temps (nb. cycles) et la population de chaque espèce au dessus de la zone d'affichage
void afficher_infos(int temps, int nb_proies, int nb_preds);    

//Affiche une case (un cercle) à la position fournie de la couleur fournie
void afficher_case(int lig, int col, int dimy, int dimx, int couleur); 

//Permet d'effacer la zone d'affichage au complet
void effacer_zone_environnement(int dimy, int dimx);

//Permet de faire une pause de "msec" millisecondes à l'écran
void delai_ecran(int msec);

//Retourne 1 si une touche a été pesée, 0 sinon.
int  touche_pesee();

//Pour récupérer un caractère saisi dans la console graphique.
int  obtenir_touche();

//Va fermer la fenêtre graphique
void fermer_mode_graphique();
//*******************************************************************************/
#define CHAR_W 5
#define CHAR_H 7
#define MAX_CHARS 26

static const unsigned char font5x7[MAX_CHARS][CHAR_H] = {
    // A
    { 0b01110,
      0b10001,
      0b10001,
      0b11111,
      0b10001,
      0b10001,
      0b10001 },
    // B
    { 0b11110,
      0b10001,
      0b10001,
      0b11110,
      0b10001,
      0b10001,
      0b11110 },
    // C
    { 0b01110,
      0b10001,
      0b10000,
      0b10000,
      0b10000,
      0b10001,
      0b01110 },
    // D
    { 0b11100,
      0b10010,
      0b10001,
      0b10001,
      0b10001,
      0b10010,
      0b11100 },
    // E
    { 0b11111,
      0b10000,
      0b10000,
      0b11110,
      0b10000,
      0b10000,
      0b11111 },
    // F
    { 0b11111,
      0b10000,
      0b10000,
      0b11110,
      0b10000,
      0b10000,
      0b10000 },
    // G
    { 0b01110,
      0b10001,
      0b10000,
      0b10111,
      0b10001,
      0b10001,
      0b01110 },
    // H
    { 0b10001,
      0b10001,
      0b10001,
      0b11111,
      0b10001,
      0b10001,
      0b10001 },
    // I
    { 0b01110,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b01110 },
    // J
    { 0b00111,
      0b00010,
      0b00010,
      0b00010,
      0b10010,
      0b10010,
      0b01100 },
    // K
    { 0b10001,
      0b10010,
      0b10100,
      0b11000,
      0b10100,
      0b10010,
      0b10001 },
    // L
    { 0b10000,
      0b10000,
      0b10000,
      0b10000,
      0b10000,
      0b10000,
      0b11111 },
    // M
    { 0b10001,
      0b11011,
      0b10101,
      0b10101,
      0b10001,
      0b10001,
      0b10001 },
    // N
    { 0b10001,
      0b11001,
      0b10101,
      0b10011,
      0b10001,
      0b10001,
      0b10001 },
    // O
    { 0b01110,
      0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b01110 },
    // P
    { 0b11110,
      0b10001,
      0b10001,
      0b11110,
      0b10000,
      0b10000,
      0b10000 },
    // Q
    { 0b01110,
      0b10001,
      0b10001,
      0b10001,
      0b10101,
      0b10010,
      0b01101 },
    // R
    { 0b11110,
      0b10001,
      0b10001,
      0b11110,
      0b10100,
      0b10010,
      0b10001 },
    // S
    { 0b01111,
      0b10000,
      0b10000,
      0b01110,
      0b00001,
      0b00001,
      0b11110 },
    // T
    { 0b11111,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b00100 },
    // U
    { 0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b01110 },
    // V
    { 0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b10001,
      0b01010,
      0b00100 },
    // W
    { 0b10001,
      0b10001,
      0b10001,
      0b10101,
      0b10101,
      0b10101,
      0b01010 },
    // X
    { 0b10001,
      0b10001,
      0b01010,
      0b00100,
      0b01010,
      0b10001,
      0b10001 },
    // Y
    { 0b10001,
      0b10001,
      0b01010,
      0b00100,
      0b00100,
      0b00100,
      0b00100 },
    // Z
    { 0b11111,
      0b00001,
      0b00010,
      0b00100,
      0b01000,
      0b10000,
      0b11111 }
};
void draw_text(const char *s, int x0, int y0, int couleur);
void draw_char(char c, int x, int y, int couleur);

#endif
