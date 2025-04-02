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
