#include "main.h"



void vider_ocean(t_ocean *ocean) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            (*ocean)[i][j].contenu = VIDE;
            (*ocean)[i][j].animal = NULL;
        }
    }
}
void* obtenir_reference_case_grille(int posx, int posy, t_ocean *ocean) {
    // Vérification des bornes
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR) {
        return NULL;
    }
    // Retourne directement le pointeur animal
    return (*ocean)[posy][posx].animal;
}

int inserer_contenu_pointeur_case_grille(int posx, int posy, t_ocean *ocean,
                                         t_contenu contenu, void *animal) {
    // Vérification des bornes
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR) {
        return 0;
    }

    // Validation du contenu
    if (contenu != VIDE && contenu != POISSON && contenu != REQUIN) {
        return 0;
    }

    // Cohérence entre contenu et pointeur
    if ((contenu == VIDE && animal != NULL) ||
        ((contenu == POISSON || contenu == REQUIN) && animal == NULL)) {
        return 0;
    }

    // Modification de la case
    (*ocean)[posy][posx].contenu = contenu;
    (*ocean)[posy][posx].animal = animal;

    return 1;
}

int effacer_contenu_case_grille(int posx, int posy, t_ocean *ocean) {
    // Vérification des bornes
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR) {
        return 0;
    }

    // Réinitialisation de la case
    (*ocean)[posy][posx].contenu = VIDE;
    (*ocean)[posy][posx].animal = NULL;


    return 1;  // Succès
}

int nombre_case_voisine_libre(int posx, int posy, t_ocean *ocean) {
    // Vérification des bornes
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR) {
        return -1;
    }

    int count = 0;

    // Vérifie les 8 directions possibles
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            // Ignore la case centrale
            if (dx == 0 && dy == 0) continue;

            int nx = posx + dx;
            int ny = posy + dy;

            // Vérifie si dans les limites
            if (nx >= 0 && nx < LARGEUR && ny >= 0 && ny < HAUTEUR) {
                if ((*ocean)[ny][nx].contenu == VIDE) {
                    count++;
                }
            }
        }
    }

    return count;
}

int choix_aleatoire_case_voisine_libre(int posx, int posy, t_ocean* ocean, int* newx, int* newy) {
    const struct { int dx; int dy; } deplacements[8] = {
            [HAUT]    = { 0, -1}, [HAUT_DR] = { 1, -1},
            [DROITE]  = { 1,  0}, [BAS_DR]  = { 1,  1},
            [BAS]     = { 0,  1}, [BAS_G]   = {-1,  1},
            [GAUCHE]  = {-1,  0}, [HAUT_G]  = {-1, -1}
    };

    t_direction directions_valides[8];
    int nb_valides = 0;

    // Vérifier chaque direction possible
    for (int i = 0; i < 8; i++) {
        int nx = posx + deplacements[i].dx;
        int ny = posy + deplacements[i].dy;

        // Gestion du wrap-around horizontal
        if (nx < 0) nx = LARGEUR - 1;
        else if (nx >= LARGEUR) nx = 0;

        // Vérifier si la case est valide et vide
        if (ny >= 0 && ny < HAUTEUR && (*ocean)[ny][nx].contenu == VIDE) {
            directions_valides[nb_valides++] = (t_direction)i;
        }
    }

    if (nb_valides == 0) {
        *newx = posx;
        *newy = posy;
        return 0;
    }

    // Choisir une direction aléatoire
    t_direction choix = directions_valides[alea(0, nb_valides - 1)];
    *newx = posx + deplacements[choix].dx;
    *newy = posy + deplacements[choix].dy;

    // Gestion finale du wrap-around
    if (*newx < 0) *newx = LARGEUR - 1;
    else if (*newx >= LARGEUR) *newx = 0;

    return 1;
}
 
int dessiner_ocean(t_ocean* ocean, int temps) {
    // Initialisation des compteurs
    int nb_proies = 0;
    int nb_preds = 0;

    // Couleurs
    const int COLOR_BLEU = BLUE;     // 1
    const int COLOR_ROUGE = RED;     // 4
    const int COLOR_NOIR = BLACK;    // 0

    // Effacer l'écran
    effacer_zone_environnement(HAUTEUR, LARGEUR);

    // Dessiner chaque case
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            // Utiliser un tableau pour stocker les couleurs et les compteurs
            static const int couleurs[] = { COLOR_NOIR, COLOR_BLEU, COLOR_ROUGE };
            static const int increments[] = { 0, 1, 1 }; // Incrément pour nb_proies et nb_preds

            // Déterminer la couleur et mettre à jour les compteurs
            int contenu = (*ocean)[y][x].contenu;
            int couleur = couleurs[contenu];
            if (contenu == POISSON) nb_proies += increments[contenu];
            else if (contenu == REQUIN) nb_preds += increments[contenu];

            // Dessiner un cercle
            afficher_case(y, x, HAUTEUR, LARGEUR, couleur);
        }
    }

    // Afficher les infos
    afficher_infos(temps, nb_proies, nb_preds);

    // Pause de 10ms
    delai_ecran(1);

    return 1;
}