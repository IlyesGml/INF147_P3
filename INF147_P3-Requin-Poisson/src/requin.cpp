// requin.cpp
//
// // implementation des fonctions pour la gestion des requins dans l'océan
//
#include "main.h"

int initialise_requin(t_liste_requin** tete_requin, t_ocean* ocean, int quantite) {
    // Vérification des entrées
    if (quantite < 0) return 0;
    if (quantite == 0) return 1;  // Rien à faire

    printf("Début initialisation de %d requins...\n", quantite);

    t_animal requin;
    int requins_places = 0;

    for (int i = 0; i < quantite; i++) {
        // Initialisation des propriétés du requin
        requin.age = alea(0, MAX_AGE_REQUIN);
        requin.energie_sante = alea(1, ENERGIE_DIGESTION*2);
        requin.jrs_gest = (requin.age >= NB_JRS_PUB_REQUIN) ? (alea(1,NB_JRS_GEST_REQUIN)) : 0;

        // Recherche d'une position vide
        int essais = 0;
        int position_trouvee = 0;

        while (essais < MAX_ESSAIS && !position_trouvee) {
            requin.posx = alea(0, LARGEUR - 1);
            requin.posy = alea(0, HAUTEUR - 1);

            if ((*ocean)[requin.posy][requin.posx].contenu == VIDE) {
                position_trouvee = 1;
            }
            essais++;
        }

        // Si pas de position vide trouvée
        if (!position_trouvee) {
            printf("Attention : seulement %d/%d requins placés\n", requins_places, quantite);
            return (requins_places > 0) ? 1 : 0;
        }

        // Placement du requin
        (*ocean)[requin.posy][requin.posx].contenu = REQUIN;
        t_liste_requin* nouveau = insererEnTete(tete_requin, requin);
        if (nouveau == NULL) {
            printf("Erreur mémoire !\n");
            return (requins_places > 0) ? 1 : 0;
        }

        (*ocean)[requin.posy][requin.posx].animal = nouveau;
        requins_places++;
    }

    printf("%d requins initialisés avec succès\n", requins_places);
    return 1;
}

int deplacer_requin_1_case(t_noeud* requin, t_ocean *ocean) {
    int posx_temp = requin->animal.posx;
    int posy_temp = requin->animal.posy;
    int nouvelle_posx, nouvelle_posy;
    t_direction dir;
    int tentatives = 0;
    const int MAX_TENTATIVES = 8;

    do {
        // Choix aléatoire d'une case voisine
        dir = choix_aleatoire_case_voisine_libre(posx_temp, posy_temp, ocean, &nouvelle_posx, &nouvelle_posy);
        tentatives++;

        // Gestion du "wrap-around" horizontal
        if (nouvelle_posx < 0) nouvelle_posx = LARGEUR - 1;
        else if (nouvelle_posx >= LARGEUR) nouvelle_posx = 0;

        // Vérifier si la case est valide et vide
        if (nouvelle_posy >= 0 && nouvelle_posy < HAUTEUR &&
            (*ocean)[nouvelle_posy][nouvelle_posx].contenu == VIDE) {
            break;
        }

        // Condition de sortie si trop de tentatives
        if (tentatives >= MAX_TENTATIVES) {
            return 0; // Échec du déplacement
        }

    } while (1);

    // Mise à jour de la grille
    if (!inserer_contenu_pointeur_case_grille(nouvelle_posx, nouvelle_posy, ocean, REQUIN, &(requin->animal))) {
        return 0;
    }

    // Mise à jour des coordonnées
    requin->animal.posx = nouvelle_posx;
    requin->animal.posy = nouvelle_posy;

    // Nettoyage ancienne position
    if (!effacer_contenu_case_grille(posx_temp, posy_temp, ocean)) {
        // En cas d'échec, annuler le déplacement
        effacer_contenu_case_grille(nouvelle_posx, nouvelle_posy, ocean);
        requin->animal.posx = posx_temp;
        requin->animal.posy = posy_temp;
        return 0;
    }

    return 1; // Succès
}

int compter_requins(t_liste_requin* liste) {
    int nb_requin = 0;
    t_liste_requin* courant = liste;

    // Parcours de toute la liste
    while (courant != NULL) {
        nb_requin++;
        courant = courant->suivant;
    }

    return nb_requin;
}

int nouveau_requin(t_liste_requin** liste, t_animal* parent, t_ocean* ocean) {
    // 1. Trouver une case voisine libre
    int new_x, new_y;
    t_direction dir = choix_aleatoire_case_voisine_libre(parent->posx, parent->posy, ocean, &new_x, &new_y);

    // Si aucune case libre, on considère quand même la reproduction comme réussie
    if (dir == 8) {
        reset_gestation(parent, 0); // Réinitialiser la gestation du parent
        return 1; // Reproduction réussie même sans case libre
    }

    // 2. Création du bébé requin avec les paramètres spécifiés
    t_animal bebe;
    init_animal(&bebe, new_x, new_y, 0, ENERGIE_DIGESTION, 0);

    // 3. Insertion dans la liste
    t_liste_requin* nouveau = insererEnTete(liste, bebe);

    // 4. Mise à jour de l'océan
    inserer_contenu_pointeur_case_grille(new_x, new_y, ocean, REQUIN, &(nouveau->animal));

    // 5. Mise à jour du parent
    reset_gestation(parent, 0); // Remise à zéro de la gestation


    return 1; // Toujours réussi selon spécification
}


int mort_requin(t_liste_requin** liste, t_ocean* ocean) {
    // Vérification des paramètres
    if (liste == NULL || *liste == NULL || ocean == NULL) {
        fprintf(stderr, "Paramètres invalides\n");
        return 0;
    }

    t_liste* courant = *liste;

    // Récupération des coordonnées du requin
    int posx = courant->animal.posx;
    int posy = courant->animal.posy;

    // Vérification des coordonnées
    if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= HAUTEUR) {
        fprintf(stderr, "Coordonnées invalides (%d,%d)\n", posx, posy);
        return 0;
    }

    // Suppression de la tête
    *liste = courant->suivant;

    // Nettoyage de la case dans l'océan
    (*ocean)[posy][posx].contenu = VIDE;
    (*ocean)[posy][posx].animal = NULL;

    // Libération mémoire
    free(courant);

    return 1;
}

