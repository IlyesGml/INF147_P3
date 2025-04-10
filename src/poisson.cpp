// poisson.cpp
//
// // Implementation des fonctions pour la gestion des poissons dans l'océan
//
#include "main.h"

int initialise_poisson(t_liste_poisson** tete_poisson, t_ocean* ocean, int quantite)
{
    printf("Initialisation de la liste des poissons avec initialize_poisson...\n");
    t_animal temp_animal;
    int essai;

    for (int i = 0; i < quantite; i++)
    {
        temp_animal.age = alea(0, MAX_AGE_POISSON);
        temp_animal.energie_sante = alea(0, ENERGIE_INIT_POISSON);
        temp_animal.jrs_gest = 0;

        while (((*ocean)[temp_animal.posx][temp_animal.posy].contenu != VIDE) && (essai < MAX_ESSAIS))
        {
            temp_animal.posx = alea(0, LARGEUR);
            temp_animal.posy = alea(0, HAUTEUR);
            essai++;
        }
        if (essai >= MAX_ESSAIS)
        {
            printf("Erreur : impossible de placer tous les poissons, trop peu de cases vides.\n");
            libererListe(*tete_poisson);
            *tete_poisson = NULL;
            return 0;
        }
        (*ocean)[temp_animal.posy][temp_animal.posx].contenu = POISSON;
        (*ocean)[temp_animal.posy][temp_animal.posx].animal = insererEnTete(tete_poisson, temp_animal);
        inserer_contenu_pointeur_case_grille(temp_animal.posx, temp_animal.posy, ocean, POISSON, (*ocean)[temp_animal.posy][temp_animal.posx].animal);
    }
    return 1;
}