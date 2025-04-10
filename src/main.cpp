/**
 * @file main.c
 * @brief
 * @ Modified by: Your name
 * @ Modified time: 2025-04-09 22:01:52
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
#ifdef TEST_OCEAN
    // Test de la fonction vider_ocean
    printf("Test de la fonction vider_ocean :\n");
    t_ocean ocean;
    int temps = 0;

    printf("=== Debut des tests ===\n");

    // Test 1: Vider l'ocean
    vider_ocean(&ocean);
    printf("1. Ocean vide : %s\n",
           (ocean[0][0].contenu == VIDE && ocean[0][0].animal == NULL) ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 2: Insertion de contenus
    t_animal poisson = {50, 1};
    t_animal requin = {100, 2};

    inserer_contenu_pointeur_case_grille(10, 10, &ocean, POISSON, &poisson);
    inserer_contenu_pointeur_case_grille(20, 20, &ocean, REQUIN, &requin);

    printf("2. Insertions : %s\n",
           (ocean[10][10].contenu == POISSON && ocean[20][20].contenu == REQUIN) ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 3: Obtenir reference
    t_animal *ref = (t_animal *)obtenir_reference_case_grille(10, 10, &ocean);
    printf("3. Reference obtenue : %s\n", (ref == &poisson) ? "SUCCES" : "ECHEC");

    // Test 4: Effacer une case
    effacer_contenu_case_grille(10, 10, &ocean);
    printf("4. Case effacee : %s\n",
           (ocean[10][10].contenu == VIDE && ocean[10][10].animal == NULL) ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 5: Cases voisines libres
    int libres = nombre_case_voisine_libre(20, 20, &ocean);
    printf("5. Nombre de cases voisines libres : %d (valeur attendue : 7 ou 8)\n", libres);

    // Test 6: Choix aleatoire
    int newx, newy;
    t_direction dir = choix_aleatoire_case_voisine_libre(20, 20, &ocean, &newx, &newy);
    if (dir != -1)
    {
        printf("6. Deplacement aleatoire vers (%d, %d) - Direction : %d\n", newx, newy, dir);
        inserer_contenu_pointeur_case_grille(newx, newy, &ocean, REQUIN, &requin);
    }
    else
    {
        printf("6. Aucune case libre trouvee autour de la position\n");
    }
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 7: Remplissage aleatoire
    printf("7. Remplissage aleatoire de l'ocean (visualisation)\n");
    for (int i = 0; i < 50; i++)
    {
        int x = alea(0, LARGEUR - 1);
        int y = alea(0, HAUTEUR - 1);
        if (ocean[y][x].contenu == VIDE)
        {
            t_animal *a = (t_animal *)malloc(sizeof(t_animal));
            a->energie_sante = alea(10, 100);
            a->age = 0;
            inserer_contenu_pointeur_case_grille(x, y, &ocean,
                                                 (a->energie_sante > 50) ? REQUIN : POISSON, a);
        }
        if (i % 10 == 0)
        {
            dessiner_ocean(&ocean, temps++);
            delai_ecran(200);
        }
    }
    dessiner_ocean(&ocean, temps++);
    delai_ecran(2000);

    // Nettoyage memoire
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            if (ocean[y][x].animal != NULL)
            {
                free(ocean[y][x].animal);
            }
        }
    }

    printf("=== Tests termines avec succes ===\n");
    printf("Appuyez sur une touche pour quitter...\n");

    while (!touche_pesee())
        ;
    obtenir_touche();

    fermer_mode_graphique();
    return 0;
#endif
#ifdef TEST_INIT_POISSON
    printf("Test d'initialisation de la liste des poissons :\n");

    t_ocean ocean;
    t_liste_poisson *liste_poisson = NULL; // creation d'une liste
    int temps;
    t_animal poissonTest = {10, 10, 0, 0, 0}; // Initialisation d'un poisson de test

    int quantite = alea(1, MAX_POISSON);
    initialise_poisson(&liste_poisson, &ocean, quantite); // Initialisation de la liste des poissons
    printf("Liste des poissons initialisee avec %d poissons.\n", quantite);

    printf("\n\n=== Debut des tests ===\n");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

#endif
#ifdef TEST_LISTE
    printf("=== Debut des tests ===\n");
    t_liste *liste = NULL;
    printf("Nombre d'insertions\nEntrez le nombre d'animaux a inserer :\n");
    int n = nombre_saisi();
    printf("\nAnimal a supprimer\nEntrez le numero de l'animal a supprimer :\n");
    int k = nombre_saisi();

    t_animal a;
    t_noeud *noeud[n];
    for (int i = 0; i < n; i++)
    {
        a.age = a.energie_sante = a.posx = a.posy = a.jrs_gest = i;
        noeud[i] = insererEnTete(&liste, a);
        printf("\nadresse de l'animal %d : %p\n", i + 1, (void *)&noeud[i]);
    }

    printf("\nListe apres %d insertions :\n", n);
    afficherListe(liste);

    int idx = k - 1;
    printf("\nSuppression de l'animal %d (noeud %p) :\n", k, (void *)noeud[idx]);
    printf("Suivant  de l'animal %d : %p\n", k, (void *)&noeud[idx]->suivant);
    printf("Precedent de l'animal %d : %p\n", k, (void *)&noeud[idx]->precedent);
    supprimerAnimal(&liste, noeud[idx]);

    printf("\nListe apres suppression du %deme :\n", k);
    afficherListe(liste);

    libererListe(liste);
#endif
    printf("======= Fin du test =======\n");
    system("pause");
    return 0;
}

int main_init(void)
{
    init_alea();
#ifdef TEST_INIT_POISSON
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
#endif
    return 0;
}
#elif TP3
int main_init(void)
{
    init_alea();
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