/******************************************************************************/
/*  UTILITAIRE_AFFICHAGE.CPP                                                  */
/*  Module utilitaire qui permet d'afficher les cases d'une grille en mode    */
/*  graphique avec le module graphique "winBGim.h".                           */
/*                                                                            */
/*  Conception : Pierre Bélisle, Eric Thé                                     */
/******************************************************************************/
#include "main.h"
#include "utilitaire_affichage.h"

//La longueur des côtés des cases en pixel
#define TAILLE_CASE_X 10  
#define TAILLE_CASE_Y 10  

//Nombre de pixels pour un caractere
#define TAILLE_CAR 24
#define TAILLE_STR 40

//marges pour la zone d'affichage des cercles
#define MARGEX 10
#define MARGEY 50
  
#define COULEUR_DEFAULT  WHITE

//*********************************
//  INIT GRAPHE
//*********************************
//Crée une fenetre de la dimension voulue
void init_graphe(int nb_cases_lignes, int nb_cases_colonnes) {  
	//la fenetre principale
	initwindow(nb_cases_colonnes*TAILLE_CASE_X, nb_cases_lignes*TAILLE_CASE_Y);   
}

//******************************
//  INIT ZONE ENVIRONNEMENT
//******************************
//Dessine un cadre blanc autour de la zone d'affichage
void init_zone_environnement(int dimy, int dimx) {
  //La fenetre de la grille
  setviewport(MARGEX, MARGEY, 
	          (dimx+1)*TAILLE_CASE_X+MARGEX+1, (dimy+1)*TAILLE_CASE_Y+MARGEY+1, 0);
  setcolor(COULEUR_DEFAULT);
  rectangle(0, 0, (dimx+1)*TAILLE_CASE_X+1, (dimy+1)*TAILLE_CASE_Y+1);
}

//******************************
//  AFFICHER CASE
//******************************
//Affiche la case reçue en paramètre à la position fournie
void afficher_case(int lig, int col, int dimy, int dimx, int couleur) {
    //On place la position pour que le symbole et la couleur soit dans la bonne case à l'écran
	int posx = (col+1)*TAILLE_CASE_X;
	int posy = (lig+1)*TAILLE_CASE_Y;

	//La vue de la grille
	setviewport(MARGEX,MARGEY,(dimx+1)*TAILLE_CASE_X+MARGEX+1, (dimy+1)*TAILLE_CASE_Y+MARGEY+1, 1);
	
	setcolor(couleur);
 	circle(posx, posy, TAILLE_CASE_X/2);
}

//******************************
//  AFFICHER INFOS
//******************************
//Affiche le temps (nb. de cycles), le nombre de proies et de prédateurs.
//
//ici on devra "gosser" pour trouver les bonnes coordonnées et positions d'affichage!
void afficher_infos(int temps, int nb_proies, int nb_preds)  {
	char val[8];

	//Établir la zone d'affichage et faire un grand rectangle rouge pour EFFACER
	setviewport(0, 0, getmaxx(), MARGEY-1, 0);
	setbkcolor(RED);
	setfillstyle(SOLID_FILL, RED);
	bar(99, 10, 990, MARGEY-10);         //rectangle rouge
	settextstyle(TRIPLEX_FONT,0,3);
	setcolor(LIGHTGRAY);

	//afficher le numéro de l'itération
	outtextxy(120, 12," Iteration : ");
	itoa(temps, val, 10);
	outtextxy(290, 12, val);

	//afficher le nombre de proies
	outtextxy(420, 12," Proies : ");
	itoa(nb_proies, val, 10);
	outtextxy(560, 12, val);

	//afficher le nombre de prédateurs
	outtextxy(700, 12," Predateurs : ");
	itoa(nb_preds, val, 10);
	outtextxy(905, 12, val);

	setbkcolor(BLACK);
}                         

//******************************
//  EFFACER ZONE ENVIRONNEMENT
//******************************
//Permet d'effacer la zone d'affichage au complet
void effacer_zone_environnement(int dimy, int dimx) {
   setviewport(MARGEX, MARGEY,
	           (dimx+1)*TAILLE_CASE_X+MARGEX+1, (dimy+1)*TAILLE_CASE_Y+MARGEY+1, 1);
   clearviewport();
}

//******************************
//  DELAI ÉCRAN
//******************************
//Permet de faire une pause de "msec" millisecondes à l'écran
void delai_ecran(int msec) {
   delay_graph(msec);
}

//******************************
//  TOUCHE PESEE
//******************************
//Retourne 1 si une touche a été pesée, 0 sinon.
int  touche_pesee() {  
   return kbhit_graph();
}

//******************************
//  OBTENIR TOUCHE
//******************************
//Pour récupérer un caractère saisi dans la console graphique.
int  obtenir_touche() {
   return getch_graph();
}

//******************************
//  FERMER MODE GRAPHIQUE
//******************************
void fermer_mode_graphique() {
	closegraph();
}
void draw_text(const char* s, int x0, int y0, int couleur)
{
    int x = x0;
    for (; *s; s++) {
        if (*s == ' ') {
            x += CHAR_W + 1;  // espace
        } else if (isupper((unsigned char)*s)) {
            draw_char(*s, x, y0,couleur);
            x += CHAR_W + 1;  // espacement entre lettres
        }
        // on peut g�rer minuscules, chiffres, etc. en �tendant la police
    }	
}
void draw_char(char c, int x, int y, int couleur) {
    if (!isupper((unsigned char)c)) return;
    int idx = c - 'A';
    for (int row = 0; row < CHAR_H; row++) {
        for (int col = 0; col < CHAR_W; col++) {
            // on teste le bit (1 = pixel plein)
            if ( (font5x7[idx][row] >> (CHAR_W-1-col)) & 1 ) {
                afficher_case(y + row, x + col, 1, 1, couleur);
            }
        }
    }
}