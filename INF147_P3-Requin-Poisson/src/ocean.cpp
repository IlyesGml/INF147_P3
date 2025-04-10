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

t_direction choix_aleatoire_case_voisine_libre(int posx, int posy, t_ocean *ocean, int *newx, int *newy) {
    // Définition des 8 directions possibles avec leurs déplacements
    const struct {
        int dx;
        int dy;
        t_direction dir;
    } directions[8] = {
            {0, -1, HAUT},     // Haut
            {1, -1, HAUT_DR},  // Haut-Droite
            {1, 0, DROITE},    // Droite
            {1, 1, BAS_DR},    // Bas-Droite
            {0, 1, BAS},       // Bas
            {-1, 1, BAS_G},    // Bas-Gauche
            {-1, 0, GAUCHE},   // Gauche
            {-1, -1, HAUT_G}   // Haut-Gauche
    };

    // Vérification des limites de la position initiale
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR) {
        *newx = posx;
        *newy = posy;
        return IMPOSSIBLE;
    }

    // Liste des directions valides
    t_direction dir_valides[8];
    int nb_dir_valides = 0;

    // Vérification de chaque direction possible
    for (int i = 0; i < 8; i++) {
        int nx = posx + directions[i].dx;
        int ny = posy + directions[i].dy;

        // Vérification des limites et si la case est vide
        if (nx >= 0 && nx < LARGEUR && ny >= 0 && ny < HAUTEUR &&
            (*ocean)[ny][nx].contenu == VIDE) {
            dir_valides[nb_dir_valides++] = directions[i].dir;
        }
    }

    // Si aucune direction valide n'a été trouvée
    if (nb_dir_valides == 0) {
        *newx = posx;
        *newy = posy;
        return IMPOSSIBLE;
    }

    // Choix aléatoire d'une direction valide
    int index_aleatoire = alea(0, nb_dir_valides - 1);
    t_direction dir_choisie = dir_valides[index_aleatoire];

    // Calcul des nouvelles coordonnées
    *newx = posx + directions[dir_choisie].dx;
    *newy = posy + directions[dir_choisie].dy;

    return dir_choisie;

}
int dessiner_ocean(t_ocean *ocean, int temps) {
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
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            // Déterminer la couleur
            int couleur;
            switch ((*ocean)[y][x].contenu) {
                case POISSON:
                    couleur = COLOR_BLEU;
                    nb_proies++;
                    break;
                case REQUIN:
                    couleur = COLOR_ROUGE;
                    nb_preds++;
                    break;
                default:
                    couleur = COLOR_NOIR;
                    break;
            }

            // Dessiner un cercle
            afficher_case(y, x, HAUTEUR, LARGEUR, couleur);
        }
    }

    // Afficher les infos
    afficher_infos(temps, nb_proies, nb_preds);

    // Pause de 10ms
    delai_ecran(10);

    return 1;
}