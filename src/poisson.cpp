// poisson.cpp
//
// // Implementation des fonctions pour la gestion des poissons dans l'océan
//
#include "main.h"

void init_poisson(t_liste_poisson* poisson, t_case *ocean, int quantite)
{
    t_noeud* noeud_temp = NULL;
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
    #ifdef DEBUG
    printf("Initialisation de la liste des poissons...\n");
    #endif
    t_animal poisson_temp = { 0, 0, 0, 0, 0 }; // Initialisation d'un poisson
    for (int i = 0; i < quantite; i++)
    {
        poisson_temp.jrs_gest = 0; // will be overridden if age >= NB_JRS_PUB_POISSON
        poisson_temp.age = alea(0, MAX_AGE_POISSON);
        poisson_temp.energie_sante = alea(1, ENERGIE_INIT_POISSON * 2);
        poisson_temp.posx = alea(0, LARGEUR);
        poisson_temp.posy = alea(0, HAUTEUR);
        noeud_temp = insererEnTete(&poisson, poisson_temp);
        if(noeud_temp == NULL)
        {
            printf("Erreur lors de l'initialisation du poisson %d.\n", i);
        }
        else
        {
            printf("Erreur lors de l'initialisation du poisson %d.\n", i);
        }
    }
}
void deplacement_poisson(t_liste_poisson* poisson,t_case *ocean, int position)
{

}
void nouveau_poisson(t_liste_poisson* poisson, t_animal* nouveau_poisson, t_case *ocean, int position)
{

}
void mort_poisson(t_liste_poisson* poisson, t_case *ocean, int position)
{
   // supprimer(poisson, position);
}