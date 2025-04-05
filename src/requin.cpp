// requin.cpp
//
// // implementation des fonctions pour la gestion des requins dans l'océan
//
#include "main.h"
/*
void init_requin(t_liste_requin *requin, int quantite)
{
    printf("Initialisation de la liste des requins...\n");
    init_liste(requin);

    for (int i = 0; i < quantite; i++)
    {
        requin->animal[i].jrs_gest = 0; // will be overridden if age >= NB_JRS_PUB_REQUIN
        requin->animal[i].age = alea(0, MAX_AGE_REQUIN);
        requin->animal[i].energie_sante = alea(1, ENERGIE_DIGESTION * 2);
        requin->animal[i].posx = alea(0, LARGEUR);
        requin->animal[i].posy = alea(0, HAUTEUR);

        if (requin->animal[i].age >= NB_JRS_PUB_REQUIN)
            requin->animal[i].jrs_gest = alea(1, NB_JRS_GEST_REQUIN);

        if (inserer(requin, requin->animal[i], i))
        {
#ifdef TEST_INIT_REQUIN
            printf("requin %d initialise : Age = %d, Energie = %d, Position = (%d, %d)\n",
                   i, requin->animal[i].age, requin->animal[i].energie_sante,
                   requin->animal[i].posx, requin->animal[i].posy);
#endif
        }
        else
        {
            printf("Erreur lors de l'initialisation du requin %d.\n", i);
        }
    }
}

void deplacement_requin(t_liste_requin *requin, int position, t_direction direction, t_ocean *ocean)
{
    int x, y;
    get_position(&requin->animal[position], &x, &y);
    // Vérification des limites de l'océan
    if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
    {
        #ifdef DEBUG
        printf("Erreur : position invalide pour le requin.\n");
        #endif
        return;
    }
    // verification dans l'ocean si  le deplacement est possible dans chaque case vvvv
    switch (direction)
    {
    case HAUT:
        y--;
        break;
    case BAS:
        y++;
        break;
    case GAUCHE:
        x--;
        break;
    case DROITE:
        x++;
        break;
    case HAUT_DR:
        x++;
        y--;
        break;
    case BAS_DR:
        x++;
        y++;
        break;
    case BAS_G:
        x--;
        y++;
        break;
    case HAUT_G:
        x--;
        y--;
        break;
    default:
        break;
    }
    set_position(&requin->animal[position], x, y);
}

void nouveau_requin(t_liste_requin *requin, t_animal *nouveau_requin, int positionParent)
{
    int x, y;
    get_position(&requin->animal[positionParent], &x, &y);
    // Vérification des limites de l'océan
    if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
    {
        #ifdef DEBUG
        printf("Erreur : position invalide pour le requin.\n");
        #endif
        return;
    }
    // verification dans l'ocean si  le deplacement est possible dans chaque case vvvv
    set_position(nouveau_requin, x, y);
    inserer(requin, *nouveau_requin, requin->taille);

}
void mort_requin(t_liste_requin *requin, int position)
{
    if (position >= 0 && position < requin->taille)
    {
        supprimer(requin, position);
        #ifdef DEBUG
        printf("Requin mort à la position %d.\n", position);
    }
    else
    {
        printf("Erreur : position invalide pour le requin.\n");
    }
    #else
    }
    #endif
}*/