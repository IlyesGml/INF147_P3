/**
 * @file main.c
 * @brief
 * @date 2025-04-01
 * @version 1.0
 */

#include "main.h"

#ifdef DEBUG
int main_debug()
{
#ifdef TESTRANDOM
    // Test de la fonction alea
    printf("Test de la fonction alea :\n");
    for (int i = 0; i < 10; i++)
    {
        int random_value = alea(0, 100);
        printf("Valeur aleatoire %d : %d\n", i + 1, random_value);
    }
#endif
#ifdef TEST_INIT_POISSON

#endif
#ifdef TEST_LISTE
    printf("Test Liste\n\n");
    t_noeud* liste = NULL; // création d'une liste vide

    t_animal poisson = { 0, 0, 0, 0, 0 }; // Initialisation d'un poisson
    t_animal requin = { 1, 1, 1, 1, 1 }; // Initialisation d'un autre poisson
    t_animal starfish = { 2, 2, 2, 2, 2 }; // Initialisation d'un autre poisson
    t_animal crab = { 3, 3, 3, 3, 3 }; // Initialisation d'un autre poisson

    printf("Poisson  : Age = %d, Energie = %d, Position = (%d, %d)\n",
        poisson.age, poisson.energie_sante, poisson.posx, poisson.posy);
    printf("Requin   : Age = %d, Energie = %d, Position = (%d, %d)\n",
        requin.age, requin.energie_sante, requin.posx, requin.posy);
    printf("Starfish : Age = %d, Energie = %d, Position = (%d, %d)\n",
        starfish.age, starfish.energie_sante, starfish.posx, starfish.posy);
    printf("Crab     : Age = %d, Energie = %d, Position = (%d, %d)\n",
        crab.age, crab.energie_sante, crab.posx, crab.posy);

    t_noeud* noeud1 = insererEnTete(&liste, poisson); // Insertion du premier poisson
    printf("\nadresse du poisson : %p\n", &noeud1);
    t_noeud* noeud2 = insererEnTete(&liste, requin); // Insertion du deuxième poisson
    printf("\nadresse du requin : %p\n", &noeud2);
    t_noeud* noeud3 = insererEnTete(&liste, starfish); // Insertion du troisième poisson
    printf("\nadresse de l'étoile de mer : %p\n\n", &noeud3);
    t_noeud* noeud4 = insererEnTete(&liste, crab); // Insertion du quatrième poisson
    printf("\nadresse du crabe : %p\n\n", &noeud4);

    afficherListe(liste); // Affichage de la liste

    printf("Suppression d'un valeur random de la liste...\n");
    switch (alea(0,3)) // Suppression d'un poisson aléatoire
    {
    case 0:
        printf("Suivant du poisson : %p\n", &noeud4->suivant);
        printf("Précédent du poisson : %p\n", &noeud4->precedent);
        supprimerAnimal(&liste,noeud4); // Suppression du poisson
        printf("Suppression du poisson :\n");
        break;

    case 1:
        printf("Suivant du requin : %p\n", &noeud3->suivant);
        printf("Précédent du requin : %p\n", &noeud3->precedent);
        supprimerAnimal(&liste,noeud3); // Suppression du requin
        printf("Suppression du requin :\n");
        break;

    case 2:
        printf("Suivant de l'étoile de mer : %p\n", &noeud2->suivant);
        printf("Précédent de l'étoile de mer : %p\n", &noeud2->precedent);
        supprimerAnimal(&liste,noeud2); // Suppression de l'étoile de mer
        printf("Suppression de l'étoile de mer :\n");
        break;
    case 3:
        printf("Suivant du crabe : %p\n", &noeud1->suivant);
        printf("Précédent du crabe : %p\n", &noeud1->precedent);
        supprimerAnimal(&liste,noeud1); // Suppression du crabe
        printf("Suppression du crabe :\n");
        break;
    default:
        break;
    }
    printf("Liste après suppression :\n");
    afficherListe(liste); // Affichage de la liste après suppression
    libererListe(liste); // Libération de la mémoire de la liste
#endif
    system("pause"); // Pause pour voir les résultats
    return 0;
}
int main_init(void)
{
    init_alea();
    return 0;
}
#elif TP3
int main_init(void)
{
    srand(time(NULL));
    return 0;
}
#endif

int main()
{
    main_init();
#ifdef DEBUG
    printf("Debug version\n");
    return main_debug();
#elif defined TP3
    printf("TP3 version\n");
    return 0

#else
    printf("No configuration defined!\n");
    return 1; // Error code
#endif
}
