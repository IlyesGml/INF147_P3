#include "main.h"
#include "liste.h"

// Initialisation de la liste vide
/**
 * @brief créer une liste avec le premier animal.
 *
 * @param animal Poisson ou requin à ajouter à la première position de la liste.
 *
 * @return t_noeud*
 */
t_noeud* creer_noeud(t_animal animal)
{
    t_noeud* nouveau_noeud = (t_noeud*)malloc(sizeof(t_noeud));
    if (nouveau_noeud == NULL)
    {
        printf("Erreur d'allocation de mémoire pour le noeud.\n");
        return NULL;
    }
    nouveau_noeud->animal = animal;
    nouveau_noeud->precedent = NULL;
    nouveau_noeud->suivant = NULL;
    return nouveau_noeud;
}
/**
 * @brief Ajouter un poisson ou requin à la tête de la liste.
 *
 * @param liste t_liste_requins ou t_liste_poissons sont la destination du nouveau poisson ou requin.
 * @param animal le poisson ou requin à ajouter à la liste dans t_liste.
 */
t_noeud* insererEnTete(t_liste** tete, t_animal animal)
{
    t_noeud* nouveau_noeud = creer_noeud(animal);
    if (nouveau_noeud == NULL)
    {
        printf("Erreur d'allocation de mémoire pour le noeud.\n");
        return NULL;
    }
    if (*tete == NULL)
    {
        *tete = nouveau_noeud;
        #ifdef DEBUG
        printf("Liste vide, Tete: %p\n", tete);
        #endif
        return nouveau_noeud;
    }
    else
    {
        nouveau_noeud->suivant = *tete;
        (*tete)->precedent = nouveau_noeud;
        *tete = nouveau_noeud;
    }
    return nouveau_noeud;
}

void supprimerEnTete(t_liste** liste)
{
    if (*liste == NULL)
    {
        printf("Erreur : la liste est vide.\n");
        return;
    }
    t_noeud* noeud_a_supprimer = *liste;
    if ((*liste)->suivant == NULL)
    {
        free(noeud_a_supprimer);
        *liste = NULL;
    }
    else
    {
        *liste = (*liste)->suivant;
        (*liste)->precedent = NULL;
        free(noeud_a_supprimer);
    }
}

void supprimerAnimal(t_noeud* animal_to_kill)
{
    if (animal_to_kill == NULL)
    {
        printf("Erreur : le noeud à supprimer est NULL.\n");
        return;
    }
    if ((animal_to_kill->precedent == NULL) && (animal_to_kill->suivant == NULL))
    {
        printf("Erreur : le noeud à supprimer est le premier ou le dernier.\n");
        return;
    }

    t_noeud* pre_noeud = animal_to_kill->precedent;
    t_noeud* next_noeud = animal_to_kill->suivant;
    pre_noeud->suivant = animal_to_kill->suivant;
    next_noeud->precedent = animal_to_kill->precedent;
    free(animal_to_kill);
}

void libererListe(t_liste* liste)
{
    t_noeud* courant;
    while (liste != NULL)
    {
        courant = liste;
        liste = liste->suivant;
        free(courant);
    }
}

void afficherListe(t_liste* liste)
{
    t_noeud* courant = liste;
    int i;
    while (courant != NULL)
    {
        i++;
        printf("Animal %c : Age = %d, Energie = %d, Position = (%d, %d)\n",i,
            courant->animal.age, courant->animal.energie_sante,
            courant->animal.posx, courant->animal.posy);
        courant = courant->suivant;
    }
    printf("\n");
}
