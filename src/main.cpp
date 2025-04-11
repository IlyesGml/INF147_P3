/**
 * @file main.c
 * @brief
 * @ Modified by: Your name
 * @ Modified time: 2025-04-10 20:22:43
 */

#include "main.h"
#ifdef DEBUG
int main_debug() {
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
    printf("\n=== TEST initialise_poisson() ===\n");
    t_ocean ocean = { VIDE, NULL };
    t_liste_poisson* liste_poisson = NULL;
    int temps = 0;

    // Initialize graphics
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);

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
    liste_poisson = NULL;  // Reset list
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

    printf("\n=== Tous les tests completes ===\n");
    while (!touche_pesee());
    obtenir_touche();
    fermer_mode_graphique();
#endif
#ifdef TEST_DEPLACEMENT_POISSON

    printf("\n=== TEST deplacer_poisson_1_case() ===\n");

    // Initialisation
    t_ocean ocean;
    t_liste_poisson* liste = NULL;
    int temps = 0;

    // Initialisation graphique
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    initialise_poisson(&liste, &ocean, 1);

    // Test 1: Déplacement normal
    printf("\n--- Test 1: Deplacement normal ---\n");
    dessiner_ocean(&ocean, temps++);
    printf("Position initiale: (%d,%d)\n", (*liste).animal.posx, (*liste).animal.posy);
    delai_ecran(1000);

    int result = deplacer_poisson_1_case(liste, &ocean);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    printf("Nouvelle position: (%d,%d)\n", liste->animal.posx, liste->animal.posy);
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Test 2: Déplacement avec rebord horizontal
    printf("\n--- Test 2: Rebord horizontal ---\n");
    liste->suivant->animal.posx = LARGEUR - 1; // Position sur le bord droit
    effacer_contenu_case_grille(liste->suivant->animal.posx, liste->suivant->animal.posy, &ocean);
    inserer_contenu_pointeur_case_grille(liste->suivant->animal.posx, liste->suivant->animal.posy, &ocean, POISSON, &(liste->suivant->animal));

    dessiner_ocean(&ocean, temps++);
    printf("Position initiale: (%d,%d)\n", liste->suivant->animal.posx, liste->suivant->animal.posy);
    delai_ecran(1000);

    result = deplacer_poisson_1_case(liste->suivant, &ocean);
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    printf("Nouvelle position: (%d,%d)\n", liste->suivant->animal.posx, liste->suivant->animal.posy);
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
    liste->suivant->suivant->animal.posx = LARGEUR / 2;
    liste->suivant->suivant->animal.posy = HAUTEUR / 2;
    ocean[HAUTEUR / 2][LARGEUR / 2].contenu = POISSON;
    ocean[HAUTEUR / 2][LARGEUR / 2].animal = &(liste->suivant->suivant->animal);

    dessiner_ocean(&ocean, temps++);
    printf("Position initiale: (%d,%d)\n", liste->suivant->suivant->animal.posx, liste->suivant->suivant->animal.posy);
    delai_ecran(1000);

    result = deplacer_poisson_1_case(liste->suivant->suivant, &ocean);
    printf("Resultat: %s (attendu: ECHEC)\n", result ? "SUCCES" : "ECHEC");
    printf("Position finale: (%d,%d)\n", liste->suivant->suivant->animal.posx, liste->suivant->suivant->animal.posy);
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);

    // Nettoyage
    libererListe(liste);
    printf("\n=== Tests termines ===\n");
    while (!touche_pesee());
    obtenir_touche();
    fermer_mode_graphique();
#endif
#ifdef TEST_NOUVEAU_POISSON
    printf("\n=== TEST nouveau_poisson() ===\n");

    // Initialisation
    t_ocean ocean;
    t_liste_poisson* liste = NULL;
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    // Création parent
    t_animal parent = {
            .posx = LARGEUR / 2,
            .posy = HAUTEUR / 2,
            .age = NB_JRS_PUB_POISSON + 1,
            .energie_sante = ENERGIE_INIT_POISSON,
            .jrs_gest = NB_JRS_GEST_POISSON
    };
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
        if (nouveau_poisson(&liste, &(liste->animal), &ocean)) succes++;
        else echecs++;
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
    t_liste* liste = NULL;

    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
    vider_ocean(&ocean);

    // Création d’un poisson à insérer
    t_animal poisson = {
        .posx = LARGEUR / 2,
        .posy = HAUTEUR / 2,
        .age = 10,
        .energie_sante = ENERGIE_INIT_POISSON,
        .jrs_gest = 0
    };

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
#ifdef TEST_NOUVEAU_REQUIN
    // 1. Initialisation de l'océan et des listes
    t_ocean ocean;
    t_liste_requin* liste_requins = NULL;

    vider_ocean(&ocean);
    printf("Ocean initialise.\n");

    // 2. Création d'un requin parent
    t_animal parent;
    init_animal(&parent, 10, 10, 100, 50, NB_JRS_GEST_REQUIN); // Position (10,10), âge 100, énergie 50

    // Insertion du parent dans l'océan et la liste
    liste_requins = insererEnTete(&liste_requins, parent);
    inserer_contenu_pointeur_case_grille(10, 10, &ocean, REQUIN, &(liste_requins->animal));
    printf("Requin parent cree en position (10,10).\n");

    // 3. Test de reproduction - Cas normal
    printf("\nTest 1: Reproduction avec case voisine libre...\n");
    int result = nouveau_requin(&liste_requins, &parent, &ocean);
    printf("Resultat: %d (1=succes)\n", result);
    printf("Nombre de requins apres reproduction: %d\n", compter_requins(liste_requins));

    // Affichage des positions des requins
    t_liste_requin* current = liste_requins;
    while (current != NULL)
    {
        printf("Requin en (%d,%d) - Energie: %d\n",
            current->animal.posx, current->animal.posy, current->animal.energie_sante);
        current = current->suivant;
    }

    // 4. Test de reproduction - Océan plein
    printf("\nTest 2: Reproduction avec ocean plein...\n");
    // Remplissage de l'océan autour du parent
    for (int i = 9; i <= 11; i++)
    {
        for (int j = 9; j <= 11; j++)
        {
            if (!(i == 10 && j == 10))
            { // On évite la case du parent
                t_animal obstacle;
                init_animal(&obstacle, i, j, 50, 30, 0);
                liste_requins = insererEnTete(&liste_requins, obstacle);
                inserer_contenu_pointeur_case_grille(i, j, &ocean, REQUIN, &(liste_requins->animal));
            }
        }
    }

    result = nouveau_requin(&liste_requins, &parent, &ocean);
    printf("Resultat avec ocean plein: %d (doit etre 1 selon specifications)\n", result);

    // 5. Nettoyage
    libererListe(liste_requins);
    printf("\nTests termines.\n");


#endif
#ifdef TEST_VIDER_OCEAN

    t_ocean ocean;

    // Remplir l'océan avec des données fictives
    for (int i = 0; i < HAUTEUR; i++)
    {
        for (int j = 0; j < LARGEUR; j++)
        {
            ocean[i][j].contenu = (t_contenu)((i + j) % 3); // Alterner entre VIDE, POISSON, REQUIN
            ocean[i][j].animal = (void*)(i * 100 + j); // Pointeur fictif
        }
    }

    // Appeler la fonction à tester
    vider_ocean(&ocean);

    // Vérification
    int erreurs = 0;
    for (int i = 0; i < HAUTEUR; i++)
    {
        for (int j = 0; j < LARGEUR; j++)
        {
            if (ocean[i][j].contenu != VIDE || ocean[i][j].animal != NULL)
            {
                erreurs++;
                printf("Erreur en (%d,%d)\n", i, j);
            }
        }
    }

    if (erreurs == 0)
    {
        printf("SUCCES: vider_ocean() a correctement initialise toutes les cases\n");
    }
    else
    {
        printf("ECHEC: %d cases mal initialisees\n", erreurs);
    }

#endif
#ifdef TEST_OBTENIR_REFERENCE

    t_ocean ocean;
    vider_ocean(&ocean);

    // Créer un animal test
    t_animal test_animal;
    init_animal(&test_animal, 5, 5, 10, 20, 0);

    // Placer l'animal dans l'océan
    ocean[5][5].contenu = POISSON;
    ocean[5][5].animal = &test_animal;

    // Tests
    printf("Test 1: Case valide... ");
    void* ref = obtenir_reference_case_grille(5, 5, &ocean);
    if (ref == &test_animal)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }

    printf("Test 2: Hors limites (x)... ");
    ref = obtenir_reference_case_grille(-1, 5, &ocean);
    if (ref == NULL)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }

    printf("Test 3: Hors limites (y)... ");
    ref = obtenir_reference_case_grille(5, HAUTEUR, &ocean);
    if (ref == NULL)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }


#endif
#ifdef TEST_INSERER_CONTENU

    t_ocean ocean;
    vider_ocean(&ocean);
    t_animal animal;

    printf("Test 1: Insertion valide... ");
    int res = inserer_contenu_pointeur_case_grille(10, 10, &ocean, POISSON, &animal);
    if (res == 1 && ocean[10][10].contenu == POISSON && ocean[10][10].animal == &animal)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }

    printf("Test 2: Hors limites... ");
    res = inserer_contenu_pointeur_case_grille(-1, -1, &ocean, POISSON, &animal);
    if (res == 0)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }

    printf("Test 3: Contenu invalide... ");
    res = inserer_contenu_pointeur_case_grille(10, 10, &ocean, (t_contenu)99, &animal);
    if (res == 0)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }

    printf("Test 4: Incoherence contenu/pointeur... ");
    res = inserer_contenu_pointeur_case_grille(20, 20, &ocean, POISSON, NULL);
    if (res == 0)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }


#endif
#ifdef TEST_EFFACER_CASE
    t_ocean ocean;
    vider_ocean(&ocean);
    t_animal animal;

    // Préparer une case
    ocean[5][5].contenu = POISSON;
    ocean[5][5].animal = &animal;

    printf("Test 1: Effacement valide... ");
    int res = effacer_contenu_case_grille(5, 5, &ocean);
    if (res == 1 && ocean[5][5].contenu == VIDE && ocean[5][5].animal == NULL)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }

    printf("Test 2: Hors limites... ");
    res = effacer_contenu_case_grille(-1, -1, &ocean);
    if (res == 0)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }


#endif
#ifdef TEST_NB_CASES_LIBRES

    t_ocean ocean;
    vider_ocean(&ocean);

    // Cas 1: Toutes les cases libres
    printf("Test 1: Toutes libres... ");
    int nb = nombre_case_voisine_libre(10, 10, &ocean);
    if (nb == 8)
    {
        printf("SUCCES (%d)\n", nb);
    }
    else
    {
        printf("ECHEC (%d)\n", nb);
    }

    // Cas 2: Certaines occupées
    ocean[9][10].contenu = POISSON;  // Haut
    ocean[11][10].contenu = REQUIN;  // Bas
    printf("Test 2: 2 cases occupees... ");
    nb = nombre_case_voisine_libre(10, 10, &ocean);
    if (nb == 6)
    {
        printf("SUCCES (%d)\n", nb);
    }
    else
    {
        printf("ECHEC (%d)\n", nb);
    }

    // Cas 3: Bordure
    printf("Test 3: Position bordure... ");
    nb = nombre_case_voisine_libre(0, 0, &ocean);
    if (nb == 3)
    {
        printf("SUCCES (%d)\n", nb);
    }
    else
    {
        printf("ECHEC (%d)\n", nb);
    }

#endif
#ifdef TEST_CHOIX_ALEATOIRE

    t_ocean ocean;
    vider_ocean(&ocean);
    int newx, newy;

    // Cas 1: Toutes libres
    printf("Test 1: Toutes libres... ");
    t_direction dir = choix_aleatoire_case_voisine_libre(10, 10, &ocean, &newx, &newy);
    if (dir != IMPOSSIBLE || newx != 10 || newy != 10)
    {
        printf("SUCCES (dir=%d, new=%d,%d)\n", dir, newx, newy);
    }
    else
    {
        printf("ECHEC\n");
    }

    // Cas 2: Aucune libre
    for (int i = 9; i <= 11; i++)
    {
        for (int j = 9; j <= 11; j++)
        {
            if (i != 10 || j != 10)
            {
                ocean[j][i].contenu = POISSON;
            }
        }
    }
    printf("Test 2: Aucune libre... ");
    dir = choix_aleatoire_case_voisine_libre(10, 10, &ocean, &newx, &newy);
    if (dir == IMPOSSIBLE && newx == 10 && newy == 10)
    {
        printf("SUCCES\n");
    }
    else
    {
        printf("ECHEC\n");
    }


#endif
#ifdef TEST_DESSINER_OCEAN

    t_ocean ocean;
    vider_ocean(&ocean);

    // Initialiser le mode graphique
    init_graphe(HAUTEUR, LARGEUR);

    // Placer quelques éléments
    ocean[5][5].contenu = POISSON;
    ocean[10][10].contenu = REQUIN;

    printf("Test d'affichage...\n");
    printf("Devrait afficher 1 poisson et 1 requin\n");

    int res = dessiner_ocean(&ocean, 0);
    if (res == 1)
    {
        printf("SUCCES: dessiner_ocean a retourne 1\n");
    }
    else
    {
        printf("ECHEC: dessiner_ocean a retourne %d\n", res);
    }

    // Attendre un appui sur une touche
    printf("Appuyez sur une touche pour continuer...\n");
    getch();

    fermer_mode_graphique();

#endif
#ifdef TEST_LISTE
    printf("=== TEST LISTE ===\n");
    t_liste* liste = NULL;
    printf("Nombre d'insertions\nEntrez le nombre d'animaux a inserer :\n");
    int n = nombre_saisi();
    printf("\nAnimal a supprimer\nEntrez le numero de l'animal a supprimer :\n");
    int k = nombre_saisi();

    t_animal a;
    t_noeud* noeud[n];
    for (int i = 0; i < n; i++)
    {
        a.age = a.energie_sante = a.posx = a.posy = a.jrs_gest = i;
        noeud[i] = insererEnTete(&liste, a);
        printf("\nadresse de l'animal %d : %p\n", i + 1, (void*)&noeud[i]);
    }

    printf("\nListe apres %d insertions :\n", n);
    afficherListe(liste);

    int idx = k - 1;
    printf("\nSuppression de l'animal %d (noeud %p) :\n", k, (void*)noeud[idx]);
    printf("Suivant  de l'animal %d : %p\n", k, (void*)&noeud[idx]->suivant);
    printf("Precedent de l'animal %d : %p\n", k, (void*)&noeud[idx]->precedent);
    supprimerAnimal(&liste, noeud[idx]);

    printf("\nListe apres suppression du %deme :\n", k);
    afficherListe(liste);

    libererListe(liste);
#endif
#ifdef TEST_PREDATEUR_POISSON_OFFICIAL
    int temps = 0;
    printf("=== FINAL TEST ===\n");
    t_liste_requin* liste_requin = NULL;
    t_liste_poisson* liste_poisson = NULL;
    t_noeud* courantP = liste_poisson;
    t_noeud* courantR = liste_requin;
    t_ocean ocean;
    vider_ocean(&ocean);
    printf("Inserez le nombre de poissons a initialiser :\n");
    int result = initialise_poisson(&liste_poisson, &ocean, nombre_saisi());
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    printf("Inserez le nombre de requins a initialiser :\n");
    result = initialise_requin(&liste_requin, &ocean, nombre_saisi());
    printf("Resultat: %s\n", result ? "SUCCES" : "ECHEC");
    dessiner_ocean(&ocean, temps++);
    delai_ecran(1000);
    printf("Appuyez sur Esc pour quitter le prog.\n");
    while (1)
    {
        if (!deplacer_poisson_1_case(courantP, &ocean))
        {
            printf("ERREUR: fail deplacement poisson\n");
            return ERROR;
        }
        dessiner_ocean(&ocean, temps++);
        delai_ecran(1000);
        courantP = obtenir_prochain(courantP);
        if (!deplacer_requin_1_case(courantR, &ocean))
        {
            printf("ERREUR: fail deplacement requin\n");
            return ERROR;
        }
        dessiner_ocean(&ocean, temps++);
        delai_ecran(1000);
        courantR = obtenir_prochain(courantR);
    }


#endif
    printf("======= Fin du test =======\n");
    system("pause");
    return 0;
}


int main_init(void)
{
    init_alea();
#if defined(TEST_PREDATEUR_POISSON_OFFICIAL) ||defined(TEST_INIT_POISSON) || defined(TEST_OCEAN) || defined(TEST_DEPLACEMENT_POISSON) || defined(TEST_NOUVEAU_POISSON) || defined(TEST_MORT_POISSON) || defined(TEST_NOUVEAU_REQUIN) || defined(TEST_VIDER_OCEAN) || defined(TEST_OBTENIR_REFERENCE) || defined(TEST_INSERER_CONTENU) || defined(TEST_EFFACER_CASE) || defined(TEST_NB_CASES_LIBRES) || defined(TEST_CHOIX_ALEATOIRE) || defined(TEST_DESSINER_OCEAN) || defined(TEST_LISTE) || defined(TEST_LISTE_2)
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
#endif
    return 0;
}
#elif TP3
int main_init(void)
{
    init_alea();
    init_graphe(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);
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