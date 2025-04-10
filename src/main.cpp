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
    t_animal poisson = { 50, 1 };
    t_animal requin = { 100, 2 };

    inserer_contenu_pointeur_case_grille(10, 10, &ocean, POISSON, &poisson);
    inserer_contenu_pointeur_case_grille(20, 20, &ocean, REQUIN, &requin);

    printf("2. Insertions : %s\n",
        (ocean[10][10].contenu == POISSON && ocean[20][20].contenu == REQUIN) ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 3: Obtenir reference
    t_animal* ref = (t_animal*)obtenir_reference_case_grille(10, 10, &ocean);
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
            t_animal* a = (t_animal*)malloc(sizeof(t_animal));
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

    while (!touche_pesee());
    obtenir_touche();

    fermer_mode_graphique();
    return 0;
#endif
#ifdef TEST_INIT_POISSON
    printf("Test d'initialisation de la liste des poissons :\n");

    t_ocean ocean;
    t_liste_poisson* liste_poisson = NULL; //creation d'une liste
    int temps;
    t_animal poissonTest = { 10,10,0,0,0 }; // Initialisation d'un poisson de test

    int quantite = alea(1, MAX_POISSON);
    initialise_poisson(&liste_poisson, &ocean, quantite); // Initialisation de la liste des poissons
    printf("Liste des poissons initialisee avec %d poissons.\n", quantite);

    printf("\n\n=== Debut des tests ===\n");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

#endif
#ifdef TEST_LISTE
    printf("Test Liste\n\n");
    t_liste* liste = NULL; // création d'une liste vide

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
    switch (alea(0, 3)) // Suppression d'un poisson aléatoire
    {
    case 0:
        printf("Suivant du poisson : %p\n", &noeud4->suivant);
        printf("Précédent du poisson : %p\n", &noeud4->precedent);
        supprimerAnimal(&liste, noeud4); // Suppression du poisson
        printf("Suppression du poisson :\n");
        break;

    case 1:
        printf("Suivant du requin : %p\n", &noeud3->suivant);
        printf("Précédent du requin : %p\n", &noeud3->precedent);
        supprimerAnimal(&liste, noeud3); // Suppression du requin
        printf("Suppression du requin :\n");
        break;

    case 2:
        printf("Suivant de l'étoile de mer : %p\n", &noeud2->suivant);
        printf("Précédent de l'étoile de mer : %p\n", &noeud2->precedent);
        supprimerAnimal(&liste, noeud2); // Suppression de l'étoile de mer
        printf("Suppression de l'étoile de mer :\n");
        break;
    case 3:
        printf("Suivant du crabe : %p\n", &noeud1->suivant);
        printf("Précédent du crabe : %p\n", &noeud1->precedent);
        supprimerAnimal(&liste, noeud1); // Suppression du crabe
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
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
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
