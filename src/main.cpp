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
    /*
        t_liste poisson;
        init_poisson(&poisson, 25); // Initialisation de 25 poissons
        printf("Taille de la liste avant suppression : %d\n", poisson.taille);
        for (int i = 19; i >= 0; i--)
        {
            int alea_value = alea(0, poisson.taille - 1);
            printf("Suppression du poisson %d...\n", alea_value);
            printf("Poisson %d : Age = %d, Energie = %d, Position = (%d, %d)\n",
                alea_value, poisson.animal[alea_value].age, poisson.animal[alea_value].energie_sante,
                   poisson.animal[alea_value].posx, poisson.animal[alea_value].posy);
            supprimer(&poisson, alea(0, poisson.taille)); // Suppression de 20 poisons aleatoires
            printf("Taille de la liste durant suppression : %d\n\n", poisson.taille);
        }
        printf("Liste des poissons après suppression :\n");
        for (int i = 0; i < poisson.taille; i++)
        {
            printf("Poisson %d : Age = %d, Energie = %d, Position = (%d, %d)\n",
                   i, poisson.animal[i].age, poisson.animal[i].energie_sante,
                   poisson.animal[i].posx, poisson.animal[i].posy);
        }
        printf("\nTaille de la liste : %d\n", poisson.taille);
    */
#endif
#ifdef TEST_LISTE
    printf("Test Liste\n\n");
    t_noeud* liste = NULL; // création d'une liste vide

    t_animal poisson = { 0, 0, 0, 0, 0 }; // Initialisation d'un poisson
    t_animal requin = { 1, 1, 1, 1, 1 }; // Initialisation d'un autre poisson
    t_animal starfish = { 2, 2, 2, 2, 2 }; // Initialisation d'un autre poisson

    printf("Poisson  : Age = %d, Energie = %d, Position = (%d, %d)\n",
        poisson.age, poisson.energie_sante, poisson.posx, poisson.posy);
    printf("Requin   : Age = %d, Energie = %d, Position = (%d, %d)\n",
        requin.age, requin.energie_sante, requin.posx, requin.posy);
    printf("Starfish : Age = %d, Energie = %d, Position = (%d, %d)\n",
        starfish.age, starfish.energie_sante, starfish.posx, starfish.posy);

    t_noeud* noeud3 = insererEnTete(&liste, poisson); // Insertion du premier poisson
    printf("\nadresse du poisson : %p\n", &noeud3);
    t_noeud* noeud2 = insererEnTete(&liste, requin); // Insertion du deuxième poisson
    printf("\nadresse du requin : %p\n", &noeud2);
    t_noeud* noeud1 = insererEnTete(&liste, starfish); // Insertion du troisième poisson
    printf("\nadresse de l'étoile de mer : %p\n\n", &noeud1);

    afficherListe(liste); // Affichage de la liste

    printf("Suppression d'un valeur random de la liste...\n");
    switch (alea(0, 2))
    {
    case 0:
        printf("Suivant du poisson : %d\n", &noeud1->suivant);
        printf("Précédent du poisson : %d\n", &noeud1->precedent);
        supprimerAnimal(noeud1); // Suppression du poisson
        printf("Suppression du poisson :\n");
        break;

    case 1:
        printf("Suivant du requin : %d\n", &noeud2->suivant);
        printf("Précédent du requin : %d\n", &noeud2->precedent);
        supprimerAnimal(noeud2); // Suppression du requin
        printf("Suppression du requin :\n");
        break;

    case 2:
        printf("Suivant de l'étoile de mer : %d\n", &noeud1->suivant);
        printf("Précédent de l'étoile de mer : %d\n", &noeud1->precedent);
        supprimerAnimal(noeud1); // Suppression de l'étoile de mer
        printf("Suppression de l'étoile de mer :\n");
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
