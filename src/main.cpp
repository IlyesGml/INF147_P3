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
    #ifdef TEST_INIT_POISSON
    t_liste poisson;
    init_poisson(&poisson, 25); // Initialisation de 25 poissons
    printf("Liste des poissons après initialisation :\n");
    for (int i = 0; i < poisson.taille; i++)
    {
        printf("Poisson %d : Age = %d, Energie = %d, Position = (%d, %d)\n",
            i, poisson.animal[i].age, poisson.animal[i].energie_sante,
            poisson.animal[i].posx, poisson.animal[i].posy);
    }
    printf("Taille de la liste : %d\n", poisson.taille);
    for (int i = 0; i < 20; i++)
    {
        printf("Taille de la liste avant suppression : %d\n", poisson.taille);
        supprimer(&poisson, i); // Suppression de 20 poisson
    }
    printf("Liste des poissons après suppression :\n");
    for (int i = 0; i < poisson.taille; i++)
    {
        printf("Poisson %d : Age = %d, Energie = %d, Position = (%d, %d)\n",
            i, poisson.animal[i].age, poisson.animal[i].energie_sante,
            poisson.animal[i].posx, poisson.animal[i].posy);
    }
    printf("Taille de la liste : %d\n", poisson.taille);
    #endif
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
