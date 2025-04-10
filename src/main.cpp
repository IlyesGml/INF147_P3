/**
 * @file main.c
 * @brief
 * @ Modified by: Your name
 * @ Modified time: 2025-04-10 15:01:19
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
    printf("\n=== TEST initialise_poisson() ===\n");
    t_ocean ocean;
    t_liste_poisson *liste_poisson = NULL;
    int temps = 0;


    // Test 1: Small quantity (10 fish)
    printf("\n--- Test 1: Petite quantite (10 poissons) ---\n");
    vider_ocean(&ocean);
    int result = initialise_poisson(&liste_poisson, &ocean, 10);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 2: Medium quantity (100 fish)
    printf("\n--- Test 2: Quantite moyenne (100 poissons) ---\n");
    vider_ocean(&ocean);
    liste_poisson = NULL; // Reset list
    result = initialise_poisson(&liste_poisson, &ocean, 100);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 3: Large quantity (500 fish)
    printf("\n--- Test 3: Grande quantite (500 poissons) ---\n");
    vider_ocean(&ocean);
    liste_poisson = NULL;
    result = initialise_poisson(&liste_poisson, &ocean, 500);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 4: Edge case - zero fish
    printf("\n--- Test 4: Quantite zero ---\n");
    vider_ocean(&ocean);
    liste_poisson = NULL;
    result = initialise_poisson(&liste_poisson, &ocean, 0);
    printf("Resultat: %s (attendu: 1)\n", result ? "SUCCES" : "ECHEC");

    // Test 5: Error case - full ocean
    printf("\n--- Test 5: Ocean plein ---\n");
    vider_ocean(&ocean);
    // Fill ocean with sharks
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            ocean[y][x].contenu = REQUIN;
            ocean[y][x].animal = NULL;
        }
    }
    liste_poisson = NULL;
    result = initialise_poisson(&liste_poisson, &ocean, 1);
    printf("Resultat: %s (attendu: 0)\n", result ? "SUCCES" : "ECHEC");
    fermer_mode_graphique();
#endif
#ifdef TEST_DEPLACEMENT_POISSON

    printf("\n=== TEST deplacer_poisson_1_case() ===\n");

    // Initialisation
    t_ocean ocean;
    t_liste_poisson *liste = NULL;
    int temps = 0;

    // Initialisation graphique
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    // Création d'un poisson de test
    t_animal poisson_test = {
        .posx = LARGEUR / 2,
        .posy = HAUTEUR / 2,
        .age = 10,
        .energie_sante = ENERGIE_INIT_POISSON,
        .jrs_gest = 0};

    // Insertion dans la liste et l'océan
    t_liste_poisson *noeud_test = insererEnTete(&liste, poisson_test);
    inserer_contenu_pointeur_case_grille(poisson_test.posx, poisson_test.posy, &ocean, POISSON, &(noeud_test->animal));

    // Test 1: Déplacement normal
    printf("\n--- Test 1: Deplacement normal ---\n");
    dessiner_ocean(&ocean, temps++);
    printf("Position initiale: (%d,%d)\n", noeud_test->animal.posx, noeud_test->animal.posy);
    delai_ecran(1000);

    int result = deplacer_poisson_1_case(noeud_test, &ocean);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    printf("Nouvelle position: (%d,%d)\n", noeud_test->animal.posx, noeud_test->animal.posy);
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 2: Déplacement avec rebord horizontal
    printf("\n--- Test 2: Rebord horizontal ---\n");
    noeud_test->animal.posx = LARGEUR - 1; // Position sur le bord droit
    effacer_contenu_case_grille(noeud_test->animal.posx, noeud_test->animal.posy, &ocean);
    inserer_contenu_pointeur_case_grille(noeud_test->animal.posx, noeud_test->animal.posy, &ocean, POISSON, &(noeud_test->animal));

    dessiner_ocean(&ocean, temps++);
    printf("Position initiale: (%d,%d)\n", noeud_test->animal.posx, noeud_test->animal.posy);
    delai_ecran(1000);

    result = deplacer_poisson_1_case(noeud_test, &ocean);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    printf("Nouvelle position: (%d,%d)\n", noeud_test->animal.posx, noeud_test->animal.posy);
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 3: Déplacement impossible (océan plein)
    printf("\n--- Test 3: Ocean plein ---\n");
    vider_ocean(&ocean);
    // Remplir tout l'océan de requins
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            ocean[y][x].contenu = REQUIN;
            ocean[y][x].animal = NULL;
        }
    }
    // Placer notre poisson au milieu
    noeud_test->animal.posx = LARGEUR / 2;
    noeud_test->animal.posy = HAUTEUR / 2;
    ocean[HAUTEUR / 2][LARGEUR / 2].contenu = POISSON;
    ocean[HAUTEUR / 2][LARGEUR / 2].animal = &(noeud_test->animal);

    dessiner_ocean(&ocean, temps++);
    printf("Position initiale: (%d,%d)\n", noeud_test->animal.posx, noeud_test->animal.posy);
    delai_ecran(1000);

    result = deplacer_poisson_1_case(noeud_test, &ocean);
    printf("Resultat: %s (attendu: ECHEC)\n", result ? "SUCCES" : "ECHEC");
    printf("Position finale: (%d,%d)\n", noeud_test->animal.posx, noeud_test->animal.posy);
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Nettoyage
    libererListe(liste);
    printf("\n=== Tests termines ===\n");
    while (!touche_pesee())
        ;
    obtenir_touche();
    fermer_mode_graphique();
#endif
#ifdef TEST_NOUVEAU_POISSON
    printf("\n=== TEST nouveau_poisson() ===\n");

    // Initialisation
    t_ocean ocean;
    t_liste_poisson *liste = NULL;
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    // Création parent
    t_animal parent = {
        .posx = LARGEUR / 2,
        .posy = HAUTEUR / 2,
        .age = NB_JRS_PUB_POISSON + 1,
        .energie_sante = ENERGIE_INIT_POISSON,
        .jrs_gest = NB_JRS_GEST_POISSON};
    insererEnTete(&liste, parent);
    inserer_contenu_pointeur_case_grille(parent.posx, parent.posy, &ocean, POISSON, &(liste->animal));

    // Test 1: Cas normal
    printf("--- Test 1: Ajout valide ---\n");
    int result = nouveau_poisson(&liste, &(liste->animal), &ocean);
    printf("Resultat: %d (attendu: 1)\n", result);
    printf("Nombre poissons: %d\n", compter_poissons(liste));

    // Test 2: Fausse couche
    printf("\n--- Test 2: Fausse couche ---\n");
    int succes = 0, echecs = 0;
    for (int i = 0; i < 100; i++)
    {
        if (nouveau_poisson(&liste, &(liste->animal), &ocean))
            succes++;
        else
            echecs++;
        liste->animal.jrs_gest = NB_JRS_GEST_POISSON; // Reset pour nouveau test
    }
    printf("Succes: %d, Echecs: %d (=33 attendu)\n", succes, echecs);

    // Nettoyage
    libererListe(liste);
    fermer_mode_graphique();
#endif
#ifdef TEST_MORT_POISSON
    printf("\n=== TEST mort_poisson() ===\n");

    // Initialisation
    t_ocean ocean;
    t_liste *liste = NULL;

    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    // Création d’un poisson à insérer
    t_animal poisson = {
        .posx = LARGEUR / 2,
        .posy = HAUTEUR / 2,
        .age = 10,
        .energie_sante = ENERGIE_INIT_POISSON,
        .jrs_gest = 0};

    // Insertion du poisson dans la liste
    insererEnTete(&liste, poisson);

    // Insertion dans la grille
    inserer_contenu_pointeur_case_grille(poisson.posx, poisson.posy, &ocean, POISSON, &(liste->animal));

    // Vérification avant suppression
    printf("--- Avant mort_poisson() ---\n");
    printf("Poisson en (%d,%d), contenu: %d, ptr animal: %p\n",
           poisson.posx, poisson.posy,
           ocean[poisson.posy][poisson.posx].contenu,
           ocean[poisson.posy][poisson.posx].animal);
    printf("Nombre poissons: %d (attendu: 1)\n", compter_poissons(liste));

    // Test : Suppression de la tête
    int result = mort_poisson(&liste, &ocean);

    printf("\n--- Apres mort_poisson() ---\n");
    printf("Resultat: %d (attendu: 1)\n", result);
    printf("Contenu case (%d,%d): %d (attendu: 0 pour VIDE)\n",
           poisson.posx, poisson.posy,
           ocean[poisson.posy][poisson.posx].contenu);
    printf("Pointeur animal case: %p (attendu: NULL)\n",
           ocean[poisson.posy][poisson.posy].animal);
    printf("Nombre poissons: %d (attendu: 0)\n", compter_poissons(liste));

    // Nettoyage
    libererListe(liste);
    fermer_mode_graphique();
#endif
#ifdef TEST_LISTE
    printf("=== TEST LISTE ===\n");
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
#ifdef TEST_COMPTER_REQUINS

    printf("=== TEST COMPTER REQUINS ===\n");
    t_liste_requin *liste_requin = NULL;
    t_ocean ocean;
    printf("Nombre d'insertions\nEntrez le nombre de requins a inserer :\n");
    int n = nombre_saisi();
    printf("\nAnimal a supprimer\nEntrez le numero de requin a supprimer :\n");
    int k = nombre_saisi();

    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    t_animal a;
    t_noeud *noeud[n];
    for (int i = 0; i < n; i++)
    {
        a.age = a.energie_sante = a.posx = a.posy = a.jrs_gest = i;
        noeud[i] = insererEnTete(&liste_requin, a);
        inserer_contenu_pointeur_case_grille(a.posx, a.posy, &ocean, REQUIN, &(noeud[i]->animal));
    }
    printf("\nListe apres %d insertions :\n", n);
    afficherListe(liste_requin);
    printf("\ncompter_requins() : %d\n", compter_requins(liste_requin));
    printf("\nsuppression... :\n");
    int idx = k - 1;
    



#endif
    printf("======= Fin du test =======\n");
    system("pause");
    return 0;
}

int main_init(void)
{
    init_alea();
#if defined(TEST_INIT_POISSON) || defined(TEST_OCEAN) || defined(TEST_DEPLACEMENT_POISSON) || defined(TEST_NOUVEAU_POISSON) || defined(TEST_MORT_POISSON) || defined(TEST_COMPTER_REQUINS)
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