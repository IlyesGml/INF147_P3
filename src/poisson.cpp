// poisson.cpp
//
// // Implementation des fonctions pour la gestion des poissons dans l'océan
//
#include "main.h"

void init_poisson(t_liste_poisson* poisson, int quantite)
{
    printf("Initialisation de la liste des poissons...\n");
    init_liste(poisson);
    poisson->animal->jrs_gest = 0;
    for (int i = 0; i < quantite; i++)
    {
        poisson->animal->age = alea(0, MAX_AGE_POISSON);
        poisson->animal->energie_sante = alea(0, ENERGIE_DIGESTION);
        poisson->animal->posx = alea(0, LARGEUR);
        poisson->animal->posy = alea(0, HAUTEUR);
        if(inserer(poisson, poisson->animal[i], i))
        {
            printf("Poisson %d initialisé : Age = %d, Energie = %d, Position = (%d, %d)\n",
                i, poisson->animal[i].age, poisson->animal[i].energie_sante,
                poisson->animal[i].posx, poisson->animal[i].posy);
        }
        else
        {
            printf("Erreur lors de l'initialisation du poisson %d.\n", i);
        }
    }
}
void deplacement_poisson(t_liste_poisson* poisson, int position, int x, int y)
{

}
void nouveau_poisson(t_liste_poisson* poisson, t_animal* nouveau_poisson, int position)
{

}
void mort_poisson(t_liste_poisson* poisson, int position)
{
 
}