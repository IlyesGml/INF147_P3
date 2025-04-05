// poisson.cpp
//
// // Implementation des fonctions pour la gestion des poissons dans l'océan
//
#include "main.h"

void init_poisson(t_liste_poisson* poisson, int quantite)
{
    /*
    printf("Initialisation de la liste des poissons...\n");
    init_liste(poisson);
    
    for (int i = 0; i < quantite; i++)
    {
        poisson->animal[i].jrs_gest = 0;
        poisson->animal[i].age = alea(0, MAX_AGE_POISSON);
        poisson->animal[i].energie_sante = alea(0, ENERGIE_DIGESTION);
        poisson->animal[i].posx = alea(0, LARGEUR);
        poisson->animal[i].posy = alea(0, HAUTEUR);
        
        if(inserer(poisson, poisson->animal[i], i))
        {
            #ifdef TEST_INIT_POISSON
            printf("Poisson %d initialise : Age = %d, Energie = %d, Position = (%d, %d)\n",
                i, poisson->animal[i].age, poisson->animal[i].energie_sante,
                poisson->animal[i].posx, poisson->animal[i].posy);
            #endif
        }
        else
        {
            printf("Erreur lors de l'initialisation du poisson %d.\n", i);
        }
    }
        */
}
void deplacement_poisson(t_liste_poisson* poisson, int position)
{

}
void nouveau_poisson(t_liste_poisson* poisson, t_animal* nouveau_poisson, int position)
{

}
void mort_poisson(t_liste_poisson* poisson, int position)
{
   // supprimer(poisson, position);
}